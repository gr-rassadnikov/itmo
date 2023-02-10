#!/bin/bash

	cnt=1
	n=10
	while [[ $cnt -le 10 ]]; do
		echo "test $cnt"
		sudo time -f "%e" bash e2b2.bash "$cnt"
		let cnt=$cnt+1
	done
