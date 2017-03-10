#!/bin/sh
##rm -f ./output/*.txt
#cd input
#for i in *; do
#	echo running $i
#	../test.sh $i > ../output/output_$i
#done
rm -f ./output/*.txt
./test.sh ./input/login_1.txt > ./output/output_login_1.txt
./test.sh ./input/login_2.txt > ./output/output_login_2.txt
./test.sh ./input/login_3.txt > ./output/output_login_3.txt
./test.sh ./input/login_4.txt > ./output/output_login_4.txt
./test.sh ./input/login_5.txt > ./output/output_login_5.txt
./test.sh ./input/login_6.txt > ./output/output_login_6.txt
./test.sh ./input/login_7.txt > ./output/output_login_7.txt
./test.sh ./input/login_8.txt > ./output/output_login_8.txt
./test.sh ./input/login_9.txt > ./output/output_login_9.txt
./test.sh ./input/login_10.txt > ./output/output_login_10.txt
./test.sh ./input/login_11.txt > ./output/output_login_11.txt
