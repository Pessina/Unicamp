from __future__ import print_function

s = int(raw_input().split(' ')[1])
a = raw_input().split(' ')
for i in range (0, len(a)):
    a[i] = int(a[i])

res = [-1] * 101
count = 0
indice = []
for i in range(0, len(a)):
    if res[a[i]] == -1:
        count += 1
        res [a[i]] = a[i]
        indice.append(i + 1)
    if count >= s:
        break

if count == s:
    print('YES')
    for element in range(0, len(indice)):
        print(indice[element], end = ' ')
else:
    print('NO')
