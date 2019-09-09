#!/usr/bin/python3
from random import *
n=3000;
print(n)
for i in range(1, n+1):
    for j in range(1, n+1):
        x=randint(0,1000)
        if i == j:
            print(0,end="")
        else:
            if (x == 0) :
                print(0,end="")
            else :
                print(1,end="")
    print();
