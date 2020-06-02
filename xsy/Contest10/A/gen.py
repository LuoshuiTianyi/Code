from random import randint
n, K = 10000, 1000
tot = int(2e6)
print(n, K)
for i in range(n):
    m = randint(1, min(tot - (n - i), 2000))
    tot -= m
    print(m, end = " ")
    Bef = 0
    for j in range(m + 1):
        Bef = randint(Bef, 100000000)
        print(Bef, end = " ")
    print()
