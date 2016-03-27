#!/bin/bash

# Este script é usado para criar entradas estáticas nas tabelas de 
# encaminhamento do CCN. Futuramente, tenho que desenvolver um protocolo
# de roteamento para difundir prefixos.
# Este script só funciona se o nó não tiver mais do que 9 conexões. 
# Pois estou pegando a substring ${line:65:3}.
# O arquivo connections é obtido pelas conexões de mesmo nome da rede principal
# da simulação do omnetpp.
# @author eama@cin.ufpe.br

cat connections | awk '{print "ContentPrefix = /cin/ufpe , NextHop = "$5" , AccessFrom = "$1 " , UpdateTime = 0/*s*/"}' > config.tmp

declare -A Array
rm *cfg* 

while read line
do 
   
	#echo 
	
	config_file=`echo ${line:65:3} | sed 's/\.//g'`
	
	echo "config_file: $config_file"

	Array[$config_file]=$config_file

	config_file="$config_file.tmp.cfg"

	#echo $config_file
	
	line=`echo $line | sed 's/\;//g'`	
	line=`echo $line | sed 's/\ethg/eth/g'`

	echo "$line" >> $config_file
	

done < config.tmp


for i in `echo ${!Array[*]}`;do
	

	echo -e "[eInterestMode]\n\n" >> $i.cfg
	echo -e "[ePreCacheMode]" >> $i.cfg

	if [ "$i" == "RS" ]; then
  		echo -e "ContentName = /cin/ufpe/movie1    , StartChunk = 0 , ChunksCount = 10000 , UpdateTime = 0/*s*/\n\n" >> $i.cfg
		echo -e "[filePreCacheMode]" >> $i.cfg
		echo -e "ContentName = /cin/ufpe/movie , Path = /home/adriano/Documentos/ccnlite/ccn-lite-omnet/simulations/video/repo/video4.dat , UpdateTime = 0/*s*/\n\n" >> $i.cfg
	else
		echo -e "\n\n" >> $i.cfg
	fi

	echo -e "[eFwdRulesMode]" >> $i.cfg

	cat  $i.tmp.cfg >> $i.cfg

	echo -e "\n[eCommentsMode]" >> $i.cfg
	echo "------------------------------------------------------------------------------" >> $i.cfg
	echo "comments go here" >> $i.cfg
	
	echo "*.$i.ccnd.ccnScenarioFile = \"configs/$i.cfg\""
done

rm *tmp*





