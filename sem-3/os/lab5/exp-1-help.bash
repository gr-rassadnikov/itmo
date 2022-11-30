#!/bin/bash
echo "stat:" > e1-memory.log

echo "stat:" > e1-top.log

echo "stat:" > e1-process.log

exec "./mem.bash" & sleep 1

echo "start"

while [[ true ]]; do
	str=$(top -b -n1 | grep mem.bash)
	echo $str
	if [[ "$str" == "" ]]; then
		break
	fi

	top -b -n1 | grep mem.bash  >> e1-process.log
	top -b -n1 | head -5 | tail -2 >> e1-memory.log
	top -b -n1 | head -12 | tail -5 >> e1-top.log

	sleep 10
done

dmesg | grep mem.bash | tail -n2 >> e1-process.log