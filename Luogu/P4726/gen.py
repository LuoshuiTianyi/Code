from random import randint
n = int(1e5)
print(n)
print(0, end = " ")
for i in range(n - 1):
    print(randint(0, 998244352), end = " ")
