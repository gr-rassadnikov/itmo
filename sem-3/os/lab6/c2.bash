#!/bin/bash

	cnt=1
	n=20
	while [[ $cnt -le 20 ]]; do
		echo "test $cnt"
		sudo time -f "%e" bash b2.bash "$cnt"
		let cnt=$cnt+1
	done
