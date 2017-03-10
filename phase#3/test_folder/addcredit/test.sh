#!/bin/sh

#Automation attempt. Same problem.
#while IFS= read -r line; do
	#../TicketMachineFE.exe < "$1"
#done < "$1"

#executes program while using the test file as input.
#the output of this script is saved in the output folder
#stated in parent script.
./TicketMachineFE.exe < "$1"