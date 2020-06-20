n = int(input())

for i in range(0, n):
    a = input().split(' ')
    for j in range(0, len(a)):
        a[j] = int(a[j])
    a.sort()
    a0 = a[0]
    diff = a[2] - a[1]
    if (a0 <= diff):
        print(a[1] + a0)
    else:
        a[0] = a[0] - diff
        a[2] = a[1]
        small1 = int(a[0]/2)
        small2 = int(a[0]%2)
        a[0] = 0
        a[1] -= small1
        a[2] = a[2] - small1 - small2
        a.sort()
        print(a0 + a[1])
