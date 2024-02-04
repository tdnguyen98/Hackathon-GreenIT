#!/bin/bash

# This script is used to measure the power consumption of a program

# !!!for now the script only works with a .app program!!!

# Store the first command line argument in a variable
program_path=$1

# Shut off networking
networksetup -setairportpower en0 off

mkdir -p power_consumption

# Idle test of power consumption: §600 samples, every 200ms (2 minute)
sudo powermetrics -i 200 -n 600 --samplers cpu_power | awk '/CPU Power:/ || /GPU Power:/ || /ANE Power:/ || /Combined Power/ {gsub(/[^0-9]/,""); print}' >> power_consumption/idle_power_consumption.txt

# Benchmark of application power consumption: §600 samples, every 200ms (2 minutes)
open $program_path & sudo powermetrics -i 200 -n 600 --samplers cpu_power | awk '/CPU Power:/ || /GPU Power:/ || /ANE Power:/ || /Combined Power/ {gsub(/[^0-9]/,""); print}' >> power_consumption/program_power_consumption.txt
pkill -f $program_path

#input 1: path of the file containing power consumption data, input 2: time in seconds of the benchmark
./a.out "power_consumption/idle_power_consumption.txt" "120"
if [ $? -eq 0 ]; then
	./a.out "power_consumption/program_power_consumption.txt" "120"
	if [ $? -eq 0 ]; then
		echo "\nSuccess"
	else
		echo "\nFailed"
	fi
else
	echo "Failed"
fi

rm -rf power_consumption

# Reactivate networking
networksetup -setairportpower en0 on

