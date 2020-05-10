from random import randint
n = int(1e1)
X = randint(1, int(1e18))
print(n)
for i in range(1, n + 1):
    print(i, X % i)
