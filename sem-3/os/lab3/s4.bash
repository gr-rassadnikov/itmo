#!/bin/bash

./s4while.bash & pid1=$!
cpulimit --pid $pid1 --limit 10 --quiet --background
./s4while.bash & pid2=$!
./s4while.bash & pid3=$!

echo "Process 1: ${pid1}"
echo "Process 2: ${pid2}"
echo "Process 3: ${pid3}"
top -b -n 1 > s4.top
kill $pid3 
top -b -n 1 >> s4.top

kill $pid1
kill $pid2