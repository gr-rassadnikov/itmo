#!/bin/bash
echo "cnt size of array from mem.bash" > report2.log

a=()
cnt=0
while [[ true ]]; do
	a+=(1 2 3 4 5 6 7 8 9 10)
	if [[ $cnt%100000 -eq 0 ]]; then
		let len=cnt*10
		echo "$len" >> report2.log
	fi
	let cnt=cnt+1
done