#!/bin/bash
echo "start"
directory="$HOME"
source="$directory/source"
report="$directory/backup-report"

if [[ ! -d $source ]]; then
	echo "Not found /source directory"
	exit
fi
if [[ ! -f $report ]]; then
	echo "Not found /backup-report file"
	exit
fi

backupDate="$(date "+%F")"
found="f"
for (( i = 0; i < 7; i++ )); do
	if [[ -d "$directory/Backup-$(date -d "-$i day" "+%F")" ]]; then
		backupDate=$(date -d "-$i day" "+%F")
		found=$backupDate
		break
	fi
done

backupDir="$directory/Backup-$backupDate"
backupName="Backup-$backupDate"



echo "backupDir: $backupDir"
if [[ $found == "f" ]]; then
	mkdir $backupDir
	cp $source/* $backupDir
	echo "Creat new backupDir: $backupDir"
	echo "Creat new backupDir: $backupDir" >> $report
	echo "Date: $backupDate" >> $report
	echo "Name: $backupName" >> $report
	echo "Copy files:" >> $report
	ls $backupDir >> $report
	echo >> $report

else
	echo "Update backupDir: $backupDir"
	echo "Update backupDir: $backupDir" >> $report
	echo "Date: $backupDate" >> $report
	echo "Name: $backupName" >> $report
	for file in $(ls $source); do
		if [[ -f "$backupDir/$file" ]]; then
			fileSize=$(wc -c "$source/$file" | awk '{print $1}')
			fileSizeOld=$(wc -c "$backupDir/$file" | awk '{print $1}')
		
			if [[ ! $fileSize == $fileSizeOld ]]; then
				mv "$backupDir/$file" "$backupDir/$file.$backupDate"
				cp "$source/$file" $backupDir
				echo "$file $file.$backupDate" >> $report
			fi
		else
			cp "$source/$file" $backupDir
			echo "$file" >> $report
		fi

	done
	echo >> $report

fi



echo "end"