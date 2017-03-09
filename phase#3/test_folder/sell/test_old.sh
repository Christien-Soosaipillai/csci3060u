#!/bin/sh
cd input
for i in *; do
	echo running $i
		while read -r line; do
			../TicketMachineFE.exe $line |& tee ../output/output_$i
		done < $i
done


#!/bin/sh
cd input
#i="./input/login_2.txt"
for i in *; do
	echo running $i
	while IFS= read line; do
		echo "$line" | ../TicketMachineFE.exe > ../output/output_$i
		##../TicketMachineFE.exe $line > ../output/output_$i
	done < $i
done