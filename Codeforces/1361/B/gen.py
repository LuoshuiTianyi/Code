from random import randint
T = 10000
print(T)
for o in range(T):
    n, p = randint(1, 10), 2
    print(n, p)
    for i in range(n):
        print(randint(1, 10), end = " ")
    print()
