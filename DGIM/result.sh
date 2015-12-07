#!/bin/bash
N=1000000
m=10000
k=500000
for i in `seq 900`
do
	b=$(($N+$i*$m))
	head -$b data2.in | tail -$k | awk '{sum+=$1} END {printf("%d\n"),sum}' 
#	head -$b test.in | tail -$k | grep 1 -c
done
