from random import randint
n = 10
print(n, randint(2, n))
for i in range(n):
    if i == 0:
        print(0, 0)
    else:
        print(randint(-3, 3), randint(-3, 3))
