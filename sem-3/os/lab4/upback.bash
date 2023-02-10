#!/bin/bash
echo "start"
directory="$HOME"
source="$directory/source"
restore="$directory/restore"


if [[ ! -d $restore ]]; then
	echo "Not found /restore directory, let's creat it"
	mkdir $restore
else
	rm -r $restore
	mkdir $restore
fi


backupDir=$(ls $directory | grep -E "Backup-[0-9]{4}-[0-9]{2}-[0-9]{2}" | sort | tail -n 1)

if [[ -d $backupDir ]]; then
	echo "Found last /backupDir: $backupDir"

	for file in $(ls $backupDir); do
		flag=$(echo $file | grep -E "*.[0-9]{4}-[0-9]{2}-[0-9]{2}")
		if [[  "$flag" == "" ]]; then 
			cp "$backupDir/$file" "$restore/$file"
		fi
	done

else
	echo "Not found last /backupDir"
fi

echo "end"