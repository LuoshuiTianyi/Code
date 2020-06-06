from random import randint, choice
n = 5
V = 3
print(n, randint(2, n))
Dot = []
for i in range(-V, V + 1):
    for j in range(-V, V + 1):
        Dot.append([i, j])
for i in range(n):
    dot = []
    if i == 0:
        dot = [0, 0]
    else:
        dot = choice(Dot)
    print(dot[0], dot[1])
    Dot.remove(dot)
