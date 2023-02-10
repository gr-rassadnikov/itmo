#!/bin/bash
:> pipe.txt
while true; do
	read s
	if [[ "$s" == "QUIT" ]]; then
		echo "script generator sucsessfull exit"
		echo $s >> pipe.txt
		exit 0
	elif [[ $s == [[:digit:]]* || $s == "+" || $s == "*" ]]; then
		echo "$s" >> pipe.txt
	else
		echo "error" >> pipe.txt
		echo "script generator exit with error"
		exit 1
	fi
done