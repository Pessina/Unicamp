import math
n = int(raw_input())

def cast_float(a):
    for c in range(0, 3):
        a[c] = int(a[c])

for i in range(0, n):
    q = raw_input().split(' ')
    cast_float(q)
    par = impar = 0
    if (q[2] % 2 == 0):
        par = q[2]/2
    else:
        par = 1 + q[2]/2
    impar = q[2] - par
    out = q[0] * par - q[1] * impar
    print (out)
