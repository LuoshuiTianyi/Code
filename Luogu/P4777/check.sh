#!/bin/bash
AC="\u2714"
WA="\u2718"
for((cnt=1;;cnt++))
do
python3 ./gen.py > 4777.in
./4777
./std
if diff 4777.ans 4777.out;
then
	echo -e "\033[32m ${AC} Accept data-${cnt}\033[0m"
else
	echo -e "\033[31m ${WA} Wrong  data-${cnt}\033[0m"
	exit 0;
fi
done
