#!/bin/bash
res=1
mod="+"
(tail -n 0 -f pipe.txt) |
while true; do
	read s;
	case $s in
		"QUIT")
			echo "script handler sucsessfull exit"
			killall tail
			echo "result: ${res}"
			rm pipe.txt
			exit 0
			;;
		[[:digit:]]*)
			if [[ $mod == "+" ]]; then
				res=$(($res + $s))
			else
				res=$(($res * $s))
			fi
			echo "result: ${res}"
			;;
		"+")
			mod="+"
			echo "add"
			;;
		"*")
			mod="*"
			echo "mul"
			;;
		*)
			echo "script handler exit with error"
			killall tail
			rm pipe.txt
			exit 1
			;;
	esac
done
