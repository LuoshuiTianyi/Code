from random import randint
n, K = 3, 2
print(n, K)
for i in range(n):
    m = 2
    print(m, end = " ")
    Bef = 0
    for j in range(m + 1):
        Bef = randint(Bef, 3)
        print(Bef, end = " ")
    print()
