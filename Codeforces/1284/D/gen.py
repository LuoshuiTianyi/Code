from random import randint
n = 10
print(n)
for i in range(n):
    l1 = randint(1, 10)
    r1 = randint(l1, 10)
    l2 = randint(1, 10)
    r2 = randint(l2, 10)
    print(l1, r1, l2, r2)
