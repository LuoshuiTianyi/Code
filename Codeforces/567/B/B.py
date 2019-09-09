#!/usr/bin/python3
import math
l=int(input())
x=int(input())
ans=10**100001
for i in range(1,l):
    if int(x%(10**i)/(10**(i-1))) != 0 :
        X=int(x/(10**i))+int(x%(10**i))
        if X < ans:
            ans=X
print(ans)
