from random import randint
n, K = 3, 2
print(n, K)
for i in range(n):
    m = 2
    print(m, end = " ")
    for j in range(m + 1):
        print(randint(1, 3), end = " ")
    print()
