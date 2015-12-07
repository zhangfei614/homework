#!/bin/bash
N=100000
m=1000
k=50000
for i in `seq 900`
do
	b=$(($N+$i*$m))
#	head -$b data.in | tail -$k | awk '{sum+=$1} END {printf("%d\n"),sum}' 
	head -$b test.in | tail -$k | grep 1 -c
done
