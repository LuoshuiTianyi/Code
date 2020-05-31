from random import randint
n, K = 1000, 100
print(n, K)
for i in range(n):
    m = 2000
    print(m, end = " ")
    for j in range(m + 1):
        print(randint(1, 3), end = " ")
    print()
