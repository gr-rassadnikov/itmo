n="$1"

for (( cnt=1; cnt<=10; cnt++ )) 
do
	exec "./do" "$n" &
done
wait