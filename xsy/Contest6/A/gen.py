from random import randint
n, m = int(10), int(10)
V = int(n / 5)
print(n, m)
for i in range(2, n + 1):
    print(randint(1, i - 1), i, randint(0, V))
for i in range(m - n + 1):
    print(randint(1, n), randint(1, n), randint(0, V))
