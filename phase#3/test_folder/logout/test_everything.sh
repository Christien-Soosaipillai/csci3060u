#!/bin/sh
##rm -f ./output/*.txt
#cd input
#for i in *; do
#	echo running $i
#	../test.sh $i > ../output/output_$i
#done

./test.sh ./input/logout_1.txt > ./output/output_logout_1.txt
./test.sh ./input/logout_2.txt > ./output/output_logout_2.txt
./test.sh ./input/logout_3.txt > ./output/output_logout_3.txt
./test.sh ./input/logout_4.txt > ./output/output_logout_4.txt
