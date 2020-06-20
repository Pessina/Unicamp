n = raw_input()
a = raw_input().split(' ')
for i in range (0, len(a)):
    a[i] = int(a[i])
a.sort()
i1 = a[len(a)-1] - a[1]
i2 = a[len(a)-2] - a[0]
if (i1 < i2):
    print(i1)
else:
    print(i2)
