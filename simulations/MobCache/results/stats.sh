#!/bin/bash


echo "Simulation Description"
echo "************************"
echo $1
echo "************************"

repeat=10

RESULT_FILES=()

RESULT_DIR=../plots
#STAT_VECTOR=("hitRate*" "hitHop*" "rttAll" "app*" )
STAT_VECTOR=("app*")



function calculate_sca() {
	policy=$1/$2
	echo "Scalar: Calculation ...  $policy # metric: $3"
	#METRICAS="server_hit"
	#grep $3 $policy/ccn-id.sca | awk '{print $4}' | tee -a $RESULT_DIR/$1_$3.txt
	grep $3 $policy/ccn-id.sca | awk '{sum+=$4; array[NR]=$4} END {for(x=1;x<=NR;x++){sumsq+=((array[x]-(sum/NR))**2);} print sum/NR};' | tee -a $RESULT_DIR/$1_$3.txt
	
	RESULT_FILES+=("$RESULT_DIR/$1_$3.txt")
}

function calculate_vec() {

	policy=$1/$2/runid_$3
	echo "Vector: Calculation ...  $policy # metric: $4"
	scavetool vector -p "name($4)" -O out $policy/ccn-id.vec
	#Delete line which doesn't start with numeric
	if [ ! -e "out.vec" ]; then
  		echo "$4 not exists in $policy "
		return
	fi

	sed -n '/^[0-9]/p' out.vec > output.vec

	#awk '{sum+=$4; array[NR]=$4} END {for(x=1;x<=NR;x++){sumsq+=((array[x]-(sum/NR))**2);} print "mean: " sum/NR " std: " sqrt(sumsq/NR) " rows: " NR; };' output.vec

	awk '{sum+=$4; array[NR]=$4} END {for(x=1;x<=NR;x++){sumsq+=((array[x]-(sum/NR))^2);} print sum/NR};' output.vec | tee -a $RESULT_DIR/$1_$4.txt
	
	RESULT_FILES+=("$RESULT_DIR/$1_$4.txt")

	rm -f output.vec
    rm -f out.vec
}



function calculate_all() {

#Cleaning
rm -rf $RESULT_DIR
mkdir $RESULT_DIR

DIRS=`ls -l | egrep '^d' | awk '{print $9}'`

DIRS_VEC=()
for DIR in $DIRS
do
DIRS_VEC+=("${DIR}")
done

for (( j = 0 ; j < ${#STAT_VECTOR[@]} ; j++ )) do

 echo "*** ${STAT_VECTOR[$j]} ***"
	for (( i = 0 ; i < ${#DIRS_VEC[@]} ; i++ )) do

			SUBDIRS=`ls -l ${DIRS_VEC[$i]} | egrep '^d' | awk '{print $9}'`
			SUBDIR_VEC=()
			for SUBDIR in $SUBDIRS
			do
			SUBDIR_VEC+=("${SUBDIR}")
			done			
	    
		for (( k = 0 ; k < ${#SUBDIR_VEC[@]} ; k++ )) do
		
		    for (( u = 0 ; u < $repeat ; u++ )) do
			    calculate_vec ${DIRS_VEC[$i]} ${SUBDIR_VEC[$k]} $u ${STAT_VECTOR[$j]}
			    echo "calculate_vec ${DIRS_VEC[$i]} ${SUBDIR_VEC[$k]} $u ${STAT_VECTOR[$j]}"
			done
			
		done
		
	done
 echo "*** ${STAT_VECTOR[$j]} ***"
 echo ""

done

for (( j = 0 ; j < ${#STAT_SCALAR[@]} ; j++ )) do
echo "*** ${STAT_SCALAR[$j]} ***"
	for (( i = 0 ; i < ${#DIRS_VEC[@]} ; i++ )) do

			SUBDIRS=`ls -l ${DIRS_VEC[$i]} | egrep '^d' | awk '{print $9}'`
			SUBDIR_VEC=()
			for SUBDIR in $SUBDIRS
			do
			SUBDIR_VEC+=("${SUBDIR}")
			done			
	
		for (( k = 0 ; k < ${#SUBDIR_VEC[@]} ; k++ )) do
		
		    for (( u = 0 ; u < repeat ; uk++ )) do
			    calculate_sca ${DIRS_VEC[$i]} ${SUBDIR_VEC[$k]} $u ${STAT_SCALAR[$j]}
			done
		done
		
	done
 echo "*** ${STAT_SCALAR[$j]} ***"
 echo ""

done

}



function plot_all() {

cd $RESULT_DIR


for (( k = 0 ; k < ${#STAT_VECTOR[@]} ; k++ )) do
	echo "$STAT"
	FILES=`ls -l | grep ${STAT_VECTOR[$k]} | awk '{print $9}'`

	NAME="\""
	for file_plot in $FILES
	do	
NAME+="$file_plot "
	done
NAME+="\""

gnuplot  -persist  << EOF
			set grid 
			set title "${STAT_VECTOR[$k]}"
			set ylabel "${DIR}"
			set xlabel "Cache Size"
			#set xrange [1:9]
			#set xtics 1,1,9
			#plot "$file_plot" 

			plot for [id in ${NAME} ] id with linespoints title id
EOF

done


for (( k = 0 ; k < ${#STAT_SCALAR[@]} ; k++ )) do
	echo "$STAT"
	FILES=`ls -l | grep ${STAT_SCALAR[$k]} | awk '{print $9}'`

	NAME="\""
	for file_plot in $FILES
	do	
NAME+="$file_plot "
	done
NAME+="\""

gnuplot  -persist  << EOF
			set grid 
			set title "${STAT_SCALAR[$k]}"
			set ylabel "${DIR}"
			set xlabel "Cache Size"
			#set xrange [1:9]
			#set xtics 1,1,9
			#plot "$file_plot" 

			plot for [id in ${NAME} ] id with linespoints title id
EOF

done

}

function plot_relation() {

cd $RESULT_DIR
l=10
i="0.05"
for (( k = 1 ; k < 19 ; k++ )) do

gnuplot  -persist  << EOF
			set grid 
			set title "${STAT_VECTOR[$k]}"
			set ylabel "${DIR}"
			set xlabel "Cache Size"
			#set xrange [1:9]
			#set xtics 1,1,9
			#plot "$file_plot" 
set term wxt $l
			plot "./D-fix${i}_tot_mean_delay.txt" with linespoints,  "./D-fix${i}_rtt_all_pkts_*.txt" with linespoints

EOF

l=$((l + 5))
i="0.$l"

done

}

function plot_relation_diff() {

cd $RESULT_DIR
l=10
i="0.05"
VALUES="\""
for (( k = 1 ; k < 19 ; k++ )) do

paste "./D-fix${i}_tot_mean_delay.txt" "./D-fix${i}_rtt_all_pkts_*.txt" | awk '{print ($2 - $1)}' > "./D-fix${i}_diff.txt"

VALUES+="$i "

l=$((l + 5))
i="0.$l"

done

VALUES+="\""

echo $VALUES
gnuplot  -persist  << EOF
			set grid 
			set title "${STAT_VECTOR[$k]}"
			set ylabel "${DIR}"
			set xlabel "Cache Size"
	
#set term wxt $l
#set term wxt 0
#	plot "./D-fix${i}_diff.txt" with linespoints
#
			plot for [id in ${VALUES} ] "./D-fix".id."_diff.txt" with linespoints title "./D-fix".id."_diff.txt"

EOF

}

#attr:measurement($D=lcd,*$cs=900*) AND name(rtt*)
#Rename
#prename 's/^.*D-(.*\.txt)$/D_$1/'  *.txt

killall gnuplot
calculate_all
plot_all
#plot_relation
#plot_relation_diff



