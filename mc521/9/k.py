n = input()
c = input().split(' ')

for i in range(0, len(c)):
    c[i] = int(c[i])

c.sort()

out = []
for i in c:
    aux1 = out[0:int(len(out)/2)]
    aux1.append(i)
    aux1 += out[int(len(out)/2):]
    out = aux1

for i in range(0, len(out)):
    out[i] = str(out[i])

print(' '.join(out))
