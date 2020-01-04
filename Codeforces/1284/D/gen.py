from random import randint, choice
n = 5
print(n)
per=[]
L1 = 1
L2 = 1
for i in range(n):
    L1 += randint(1, 2)
    l1 = L1
    L1 += randint(1, 5)
    r1 = L1
    L2 += randint(1, 5)
    l2 = L2
    L2 += randint(1, 5)
    r2 = L2
    if randint(1, 10) == 1 and len(per):
        x = choice(per)
        l1 = randint(x[0], x[1])
        r1 = randint(l1, x[1])
        l2 = randint(x[2], x[3])
        r2 = randint(l2, x[3])
    per.append([l1, r1, l2, r2])
    print(l1, r1, l2, r2)
