#!/bin/bash

# Store the first command line argument in a variable
program_path=$1

networksetup -setairportpower en0 off
./a.out "/usr/bin/sudo /usr/bin/powermetrics -n 1 -i 1000 --samplers cpu_power"

if [ $? -eq 0 ]; then
	open $program_path & ./a.out "/usr/bin/sudo /usr/bin/powermetrics -n 6 -i 1000 --samplers cpu_power"
else
	echo "Failed"
fi

networksetup -setairportpower en0 on
