#!/bin/bash
AC="\u2714"
WA="\u2718"
for((cnt=1;;cnt++))
do
./gen.py > 3369.in
./3369
./std
if diff 3369.ans 3369.out;
then
	echo -e "\033[32m ${AC} Accept data-${cnt}\033[0m"
else
	echo -e "\033[31m ${WA} Wrong  data-${cnt}\033[0m"
	exit 0;
fi
done

