from random import randint, choice
n = 10
V = 10
print(n, randint(2, n))
Dot = []
for i in range(-V, V + 1):
    for j in range(-V, V + 1):
        Dot.append([i, j])
for i in range(n):
    if i == 0:
        
        print(0, 0)
    else:
        print()
