#!/bin/bash
echo "start"
if [[ $# -eq 0 ]]; then
	echo "Expected 1 argument, found 0"
	exit
fi
file=$1
trashDir=~/.trash
trashLog=~/.trash.log
filePath=""
fileTrashPath=""
mod="1"

cat $trashLog | while read str; do
	if [[ "$str" == "" ]]; then
		flag=$(echo $filePath | grep -E "*.$file")
		if [[ ! "$flag" == "" ]]; then 
			echo "Path to your file: $filePath"
			echo "TrashPath to your file: $fileTrashPath"
			echo "Do you want to restore this file? Please, write yes/no."
			while true; do
				read rep < /dev/tty
				if [[ "$rep" == "yes" ]]; then
					echo "start restore"
					directory=$(dirname "$filePath")
					if [[ ! -d "$directory" ]]; then
						echo "Directory: $directory does not exist, change this directory to home-directory"
						directory=$HOME
					fi

					if [[ -f "$fileTrashPath" ]]; then
						if [[ -f "$directory/$file" ]]; then
							echo "Hard-link wit this name exist, Do you want to rename your new Hard-link? Please, write yes/no. "
							while true; do
								read rep < /dev/tty
								if [[ "$rep" == "yes" ]]; then
									while true; do
										echo "Write new name:"
										read rep2 < /dev/tty
										
										if [[ $rep2 == $file ]]; then
											echo "File with this name exist, write another name!"
											continue
										fi
										ln "$fileTrashPath" "$directory/$rep2"
										rm "$fileTrashPath"
										file=$rep2
										break
									done
								elif [[ ! "$rep" == "no" ]]; then
									echo "Please, write yes/no."
									continue
								fi
								break
							done
						else 
							ln "$fileTrashPath" "$directory/$file"
							rm "$fileTrashPath"
						fi
			
					else
						echo "Hard-link: $fileTrashPath does not exist (maybe file $trashLog is old)"
					fi
			
					echo "end restore"
				elif [[ ! "$rep" == "no" ]]; then
					echo "Please, write yes/no."
					continue
				fi
				break
			done

		fi
	else
		if [[ "$mod" == "1" ]]; then
			mod="2"
			filePath=$str
		else
			mod="1"
			fileTrashPath=$str
		fi
	fi

done

echo "end"