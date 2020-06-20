s = raw_input()
n = raw_input().split(' ')

c1 = 0
c0 = 0
for i in range(0, len(n)):
    n[i] = int(n[i]) % 2
    if n[i] == 0:
        c0 += 1
    else:
        c1 += 1

if c0 == 1:
    for i in range(0, len(n)):
        if n[i] == 0:
            print(i + 1)

if c1 == 1:
    for i in range(0, len(n)):
        if n[i] == 1:
            print(i + 1)
