#!/usr/bin/python3
from random import *
n=5;
lim = 6;
print(n)
for i in range(1, n + 1):
    print(randint(0, i - 1), i, randint(1, lim), randint(1, lim))
