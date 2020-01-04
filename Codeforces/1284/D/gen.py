from random import randint
n = 5
print(n)
for i in range(n):
    l1 = randint(1, 5)
    r1 = randint(l1, 5)
    l2 = randint(1, 5)
    r2 = randint(l2, 5)
    print(l1, r1, l2, r2)
