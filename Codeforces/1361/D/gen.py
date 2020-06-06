from random import randint, choice, shuffle
n = 10002
print(n, randint(2, n))
a = []
for i in range(-100, 101):
    for j in range(-100, 101):
        a.append([i, j])
shuffle(a)
for i in a:
    print(i[0], i[1])
        #if i == 0:
        #    print(0, 0);
        #else:
        #    print(randint(-V, V), randint(-V, V))
