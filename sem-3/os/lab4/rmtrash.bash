#!/bin/bash
echo "start"
file=$1
trashDir=~/.trash
trashLog=~/.trash.log


if [[ -f $file ]]; then
	echo "l3"

	if [[ ! -d $trashDir ]]; then 
		mkdir $trashDir

	fi

	if [[ ! -f $trashLog ]]; then 
		touch $trashLog
	fi

	number=1
	while [[ -e "$trashDir/$file$cnt" ]]; do
		let number=number+1
	done

	ln "$file" "$trashDir/$file$cnt"
	rm "$file"
	echo "$file" >> $trashLog
	echo "$trashDir/$file$cnt" >> $trashLog
	echo >> $trashLog

fi
