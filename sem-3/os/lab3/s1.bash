#!bin/bash
DATE=$(date '+%d.%m.%y-%H:%M:%S')
mkdir ~/test && echo "catalog test was created successfully" > ~/report && touch ~/test/${DATE}.txt

WEB="www.net_nikogo.ru"
(ping ${WEB} -c 1) || echo "${DATE} error: can't get ping to ${WEB}" >> ~/report
