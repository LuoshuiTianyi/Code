from random import randint
n, m = int(1e5), int(2e6)
V = int(1e5)
print(n, m)
for i in range(m):
    print(randint(1, n), randint(1, n), randint(1, V))
    
