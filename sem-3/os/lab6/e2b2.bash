n="$1"

for (( cnt=1; cnt<=20; cnt++ )) 
do
	exec "./handleFiles" "file/f$cnt" &
done
wait