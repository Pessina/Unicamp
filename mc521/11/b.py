from __future__ import print_function

n = input()
word = input()
word = [x for x in word]
h = {}
for i in word:
    if i in h:
        h[i] += 1
    else:
        h[i] = 1
if 'n' in h:
    for i in range(0, h['n']):
        print('1 ', end='')
if 'z' in h:
    for i in range(0, h['z']):
        print('0 ', end='')
print()
