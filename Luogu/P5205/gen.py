from random import randint
n = 100000
print(n)
print(1, end = " ")
for i in range(n - 1):
    print(randint(0, 998244352), end = " ")
