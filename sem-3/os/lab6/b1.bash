#!/bin/bash

n="$1"

cnt=1
while [[ $cnt -le $n ]]; do
	echo "start script: $cnt"
	./do "$n"
	echo "end script: $cnt"
	let cnt=$cnt+1
done