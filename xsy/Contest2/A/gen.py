from random import randint
n, m, s = randint(1, 3), 2, randint(5, 10)
print(n, m, s)
L = 1
def Print():
    global L
    L += randint(1, 3)
    print(L, end = ' ')
for i in range(0, n):
    Print()
    Print()
    print()
