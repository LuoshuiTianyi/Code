#!/usr/bin/python3
from random import *
n=100
print(n)
cnt=1
print(1,randint(1,n*2))
for i in range(2,n+1):
    opt=randint(1,2)
    if (opt == 1):
        cnt=cnt+1
        print(1,randint(1,n*2))
    if (opt == 2):
        print(4,randint(1,cnt))
    if (opt == 3):
        print(5,randint(1,n*2))
    if (opt == 4):
        print(6,randint(1,n*2))
