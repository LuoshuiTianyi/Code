#!/usr/bin/python3
from random import *
lis="ACGT"
n=200000;m=100000;k=1
print(n,m,k)
for i in range(1,n+1):
    print(choice(lis),end="");
print()
for i in range(1,m+1):
    print(choice(lis),end="");
