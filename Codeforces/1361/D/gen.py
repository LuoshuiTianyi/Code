from random import randint, choice, shuffle
n = 500000
V = int(1e9)
print(n, randint(2, n))
for i in range(n):
    if i == 0:
        print(0, 0);
    else:
        print(randint(-V, V), randint(-V, V))
