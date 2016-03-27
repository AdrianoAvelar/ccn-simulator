#!/bin/bash

metric='appThroughput'


rm -f $metric.out
rm -f $metric.plot

function calculate() {
	echo "Calculation Cache: $1 CacheSize: $2 RunNumber: $3 Metric: $4"
	echo `scavetool vector -p \"name\($4*\)\" -O out $1/cs-$2/$3/ccn-id.vec`
	#scavetool vector -p "name($4)" -O out $1/cs-$2/$3/ccn-id.vec
	#Delete line which doesn't start with numeric
	sed -n '/^[0-9]/p' out.vec > output.vec

	awk '{sum+=$4; array[NR]=$4} END {for(x=1;x<=NR;x++){sumsq+=((array[x]-(sum/NR))**2);} print "mean: " sum/NR " std: " sqrt(sumsq/NR) " rows: " NR; };' output.vec >> $metric.out

	rm -f output.vec
	rm -f out.vec
}



for (( k = 0 ; k < 2 ; k++ )) do
calculate lce 900 $k $metric 30

done

awk '{print $2}' $metric.out > $metric.plot

echo "Result..."
cat $metric.out
echo "Ploting.."
cat $metric.plot












