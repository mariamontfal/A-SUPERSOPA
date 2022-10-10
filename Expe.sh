#!/bin/bash
Name=$1
sizeN=(2 3 4 5 6 7 8 9 10 50 100 200 300 400 500 1000)
sizeM=(3 4 5 6 7 8 9 10 11 20 30 40 50 60)

for i in "${sizeN[@]}";
do
	for j in "${sizeM[@]}";
	do
		echo date
		echo "$Name"N"${i}"M"${j}"
		./program.exe EjemploDic.txt $i $j 0 > ./Ejemplos/$Name/"$Name"N"${i}"M"${j}".txt
	done
done
