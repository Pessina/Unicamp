n = int(input())
a = []
for i in range(0, n):
    x = input().split(' ')
    a.append((int(x[0]), int(x[1])))
x = int(input())
for i in range(0, len(a)):
    if x >= a[i][0] and x <= a[i][1]:
        print(len(a) - i)
        break
