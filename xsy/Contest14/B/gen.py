from random import randint
n, m, L = int(1e6), int(2e6), int(1e4)
n, m, L = 1000000, 2000000, 26548
print(n, m, L)
for i in range(2, n + 1):
    print(randint(1, i - 1), end = " ")
print()
for i in range(1, n + 1):
    print(randint(1, min(i, L)), end = " ")
print()
for i in range(m):
    print(randint(1, L), end = " ")
print()
