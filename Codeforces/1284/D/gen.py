from random import randint
n = 1000
print(n)
per=[]
L1 = 1
L2 = 1
for i in range(n):
    L1 += randint(1, 1000)
    l1 = L1
    L1 += randint(1, 1000)
    r1 = L1
    L2 += randint(1, 1000)
    l2 = L2
    L2 += randint(1, 1000)
    r2 = L2
    if randint(1, 10) == 1:
    per.append([l1, r1, l2, r2])
    print(l1, r1, l2, r2)
