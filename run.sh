#! /bin/bash

make

echo
echo QUEUEING SYSTEMS SIMULATION 2014
echo Dimitrios Karakostas - 03110179
echo

for K in {1..9}
do

    for l in {1..3}
    do
	
        ./main $K $l >> outK$K,L$l.txt
		echo Simulation with K = $K, l = $l
		
    done
	
done

echo
