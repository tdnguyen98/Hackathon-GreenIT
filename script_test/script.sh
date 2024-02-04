#!/bin/bash

# Store the first command line argument in a variable
program_path=$1

# Shut off networking
networksetup -setairportpower en0 off

# Idle test of power consumption: one sample every 200ms, times 1500 samples: 5 minutes of sampling (300 seconds * 5 times/second)
./a.out "/usr/bin/sudo /usr/bin/powermetrics -n 1500 -i 200 --samplers cpu_power"

if [ $? -eq 0 ]; then
# Benchmark of application power consumption: 300 samples, every 200ms (1 minute)
	open $program_path & ./a.out "/usr/bin/sudo /usr/bin/powermetrics -n 300 -i 200 --samplers cpu_power"
 	sleep 6
	pkill -f $program_path
else
	echo "Failed"
fi

# Reactivate networking
networksetup -setairportpower en0 on
