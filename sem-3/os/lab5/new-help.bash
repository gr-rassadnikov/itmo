#!/bin/bash

n=8400000
k=30

cnt=1
while [[ $cnt -le $k ]]; do
	exec "./newmem.bash" "3000000" && sleep 1
	echo "run script: $cnt"
	let cnt=$cnt+1
done