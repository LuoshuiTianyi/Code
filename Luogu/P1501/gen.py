from random import randint, choice
opt = ['+', '*', '/']
n, Q = 3, 10
print(n, Q)
for i in range(2, n + 1):
    print(randint(1, i - 1), i)
for i in range(Q):
    op, u, v = choice(opt), randint(1, n), randint(1, n)
    print(op, u, v, end = " ")
    if op == '/':
        print()
    else:
        print(randint(1, 3))
