#!/bin/bash
for((i=1;;i++))
do
  ./data.py > B.in
  ./B.py < B.in > bl.out
  ./B
  if diff B.out bl.out;
  then
	  echo -e "\033[32m ${AC} Accept data-${i}\033[0m"
  else
	  echo -e "\033[31m ${WA} Wrong  data-${i}\033[0m"
	  exit 0;
  fi
done
