#!/bin/bash
echo $$ > .pid
res=1
MODE=""
usr1()
{
	MODE="+"
}
usr2()
{
	MODE="*"
}
term()
{
	MODE="TERM"
}
reset()
{
	MODE="RESET"
}
trap 'usr1' USR1
trap 'usr2' USR2
trap 'term' SIGTERM
trap 'reset' SIGURG
while true; do
	case $MODE in
		"TERM")
			echo "SIGTERM signal from script generator - script finish"
			exit 0
			;;
		"RESET")
			res=1
			;;
		"+")
			res=$(($res + 2))
			;;
		"*")
			res=$(($res * 2))
			;;
	esac
	echo $res
	MODE=""
	sleep 1
done