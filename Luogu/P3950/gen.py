from random import randint, choice
n, m, e, dl, cnt = 5, 10, [], [], 0
print(n, m)
for i in range(2, n + 1):
    e.append([randint(1, i - 1), i])
    print(e[i - 2][0], i)
def Chi():
    E = choice(e)
    print("C", E[0], E[1])
    e.remove(E)
    global cnt
    cnt = cnt + 1
    dl.append([cnt, E[0], E[1]])
def Reset():
    Dl = choice(dl)
    print("U", Dl[0])
    dl.remove(Dl)
    e.append([Dl[1], Dl[2]])
for i in range(m):
    op = randint(1, 3)
    if op == 1:
        print("Q", randint(1, n), randint(1, n))
    if not len(e):
        Reset()
        continue
    if not len(dl):
        Chi()
        continue
    if op == 2:
        Chi()
    if op == 3:
        Reset()
