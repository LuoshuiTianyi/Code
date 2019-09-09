#!/usr/bin/python3
from random import *
for l in range(1,11):
    n=1000;
    seed="abcdefghijklmnopqrstuvwxyz"
    for i in range(1,n+1):
        print(choice(seed),end="")
    print()
