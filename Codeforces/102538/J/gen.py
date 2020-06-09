from random import randint
print(1)
n, m = int(2e5), int(3e5)
print(n, m)
for i in range(2, n + 1):
    print(randint(1, i - 1), i)
for i in range(m - n + 1):
    print(randint(1, n), randint(1, n))
