#!/bin/bash


cnt=1
echo "start" 
while [[ $cnt -le 10 ]]; do
	n=1
	echo "test $cnt" 
	while [[ $n -le 20 ]]; do
		sudo time -f "%e" ./do "$n"
		let n=$n+1
	done

	let cnt=$cnt+1
done