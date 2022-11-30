#!/bin/bash
echo "cnt size of array from mem.bash" > report.log

a=()
cnt=0
while [[ true ]]; do
	a+=(1 2 3 4 5 6 7 8 9 10)
	if [[ $cnt -gt $1 ]]; then
		echo "End newmem: size of array $cnt"
		break
	fi
	let cnt=cnt+10
done