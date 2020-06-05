from random import randint
T = 100
print(T)
for o in range(T):
    n, p = randint(1, 1000), randint(1, 10)
    print(n, p)
    for i in range(n):
        print(randint(1, 1000), end = " ")
    print()
