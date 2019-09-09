#!/bin/bash
AC="\u2714"
WA="\u2718"
for((cnt=1;;cnt++))
do
./gen.py > 1812.in
./1812
./std
if diff 1812.ans 1812.out;
then
	echo -e "\033[32m ${AC} Accept data-${cnt}\033[0m"
else
	echo -e "\033[31m ${WA} Wrong  data-${cnt}\033[0m"
	exit 0;
fi
done
