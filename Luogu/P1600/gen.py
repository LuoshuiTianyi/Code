from random import randint
n = 5
m = 1
print(n, m)
for i in range(2, n + 1):
    print(randint(1, i - 1), i)
for i in range(0, n):
    print(randint(0, n), end = " ")
print()
for i in range(0, m):
    print(randint(1, n), randint(1, n))
