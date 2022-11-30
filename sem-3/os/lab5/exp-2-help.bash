#!/bin/bash
echo "stat:" > e2-memory.log

echo "stat:" > e2-top.log

echo "stat mem:" > e2-process.log
echo "stat mem2:" > e2-process2.log

exec "./mem.bash" & exec "./mem2.bash" & sleep 1

echo "start"

while [[ true ]]; do
	str=$(top -b -n1 | grep mem.bash)
	echo $str

	strr=$(top -b -n1 | grep mem2)
	echo "$strr"

	if [[ "$str" == "" && "$str2" == ""  ]]; then
		break
	fi

	top -b -n1 | grep mem.bash  >> e2-process.log
	top -b -n1 | grep mem2.bash  >> e2-process2.log
	top -b -n1 | head -5 | tail -2 >> e2-memory.log
	top -b -n1 | head -12 | tail -5 >> e2-top.log

	sleep 10
done

dmesg | grep mem.bash | tail -n2 >> e2-process.log
dmesg | grep mem2.bash | tail -n2 >> e2-process2.log