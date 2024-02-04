#bin#bash
sudo powermetrics -i 5000 -n 10 | awk '/elapsed/ {val=substr($11, 2, 7); next} /Combined Power/ && val {print val, $8; val="\t"}' >> test.txt && awk '{sum1+=$1; sum2+=$2; count++} END {print "average ms: " sum1/count, "average mW: " sum2/count}' test.txt
