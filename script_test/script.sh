#!/bin/bash

# Store the first command line argument in a variable
program_path=$1

# Shut off networking
networksetup -setairportpower en0 off

# Idle test of power consumption
./a.out "/usr/bin/sudo /usr/bin/powermetrics -n 1 -i 1000 --samplers cpu_power"

if [ $? -eq 0 ]; then
# Benchmark of application power consumption
	open $program_path & ./a.out "/usr/bin/sudo /usr/bin/powermetrics -n 6 -i 1000 --samplers cpu_power"
 	sleep 6
	pkill -f $program_path
else
	echo "Failed"
fi

# Reactivate networking
networksetup -setairportpower en0 on
