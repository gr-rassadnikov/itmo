#!/bin/bash
while true; do
	read s
	if [[ "$s" == "TERM" ]]; then
		echo "TERM in input: kill -SIGTERM"
		kill -SIGTERM $(cat .pid)
		exit 0
	elif [[ $s == "+" ]]; then
		kill -USR1 $(cat .pid)
	elif [[ $s == "*" ]]; then
		kill -USR2 $(cat .pid)
	elif [[ "$s" == "RESET" ]]; then
		kill -SIGURG $(cat .pid)
	fi
done