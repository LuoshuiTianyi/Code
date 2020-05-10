from random import randint
n = int(50)
V = int(1e18)
X = randint(1, V)
M = 1
print(n)
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)
def LCM(a, b):
    return a * b / gcd(a, b)
for i in range(n):
    a = randint(1, n)
    while LCM(M, a) > V:
        a = randint(1, V)
    print(a, X % a)
    M = LCM(M, a)
