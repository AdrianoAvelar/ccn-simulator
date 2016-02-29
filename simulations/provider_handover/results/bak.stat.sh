#!/bin/bash

echo "Simulation Description"
echo "************************"
echo $1
echo "************************"

function calculate() {
	echo "Calculation ...  $1 # column: $2"
	scavetool vector -p "name($2)" -O out D-$1/ccn-id.vec
	#Delete line which doesn't start with numeric
	sed -n '/^[0-9]/p' out.vec > output.vec

	awk '{sum+=$4; array[NR]=$4} END {for(x=1;x<=NR;x++){sumsq+=((array[x]-(sum/NR))**2);} print "mean: " sum/NR " std: " sqrt(sumsq/NR) " rows: " NR; };' output.vec

	rm -f output.vec
	rm -f out.vec
}




calculate prob_cache caching*
calculate priority_cache caching*

echo "************* HIT_RATE **************"
calculate prob_cache 		hit_rate*
calculate priority_cache 	hit_rate*
calculate btw 				hit_rate*

for ((a=1; a <= 9 ; a++)) 
do
calculate fix0.$a 			hit_rate*
done

calculate lce 				hit_rate*
calculate lcd 				hit_rate*

echo "************* HIT HOP **************"

calculate prob_cache hit_hop_*
calculate priority_cache hit_hop_*
calculate btw hit_hop_*

for ((a=1; a <= 9 ; a++)) 
do
calculate fix0.$a 			hit_hop_*
done

calculate lce hit_hop_*
calculate lcd hit_hop_*

echo "************* PSNR **************"
calculate prob_cache 		psnr_*
calculate priority_cache 	psnr_*
calculate btw 				psnr_*
for ((a=1; a <= 9 ; a++)) 
do
calculate fix0.$a 			psnr_*
done
calculate lce 				psnr_*
calculate lcd 				psnr_*


echo "************* SSIM **************"
calculate prob_cache 		ssim_*
calculate priority_cache 	ssim_*
calculate btw				ssim_*
calculate fix0.3 			ssim_*
calculate fix0.7 			ssim_*
calculate lce 				ssim_*
calculate lcd 				ssim_*

echo "************* Delay ALL PACKETS **************"
calculate prob_cache		rtt_all_pkts_*
calculate priority_cache 	rtt_all_pkts_*
calculate btw 				rtt_all_pkts_*
for ((a=1; a <= 9 ; a++)) 
do
calculate fix0.$a 			rtt_all_pkts_*
done
calculate lce 				rtt_all_pkts_*
calculate lcd 				rtt_all_pkts_*

echo "************* DELAY VIDEO **************"
calculate prob_cache 		delay_*
calculate priority_cache 	delay_*
calculate btw 				delay_*
for ((a=1; a <= 9 ; a++)) 
do
calculate fix0.$a 			delay_*
done
calculate lce 				delay_*
calculate lcd 				delay_*









