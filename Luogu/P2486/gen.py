from random import randint
n, m = 5, 5
print(n, m)
for i in range(n):
    print(randint(1, n), end = " ")
print()
for i in range(2, n + 1):
    print(randint(1, i - 1), i)
for i in range(m):
    op = randint(1, 2)
    x, y = randint(1, n), randint(1, n)
    if op == 1:
        print("C", x, y, randint(1, n))
    else:
        print("Q", x, y)
