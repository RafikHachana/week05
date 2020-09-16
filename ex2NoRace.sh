#!/bin/bash


#Check if the file exists or not
if test ! -f numbers
then 
	echo 0 > numbers
fi



if ln numbers numbers.lock
then
	for i in `seq 1 100`:
	do
		n=`tail -1 numbers`
		expr $n + 1 >>numbers
	done

	rm numbers.lock
fi


echo The last 10 numbers now are: `tail -10 numbers`
