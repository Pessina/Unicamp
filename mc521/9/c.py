from __future__ import print_function

tn = int(raw_input())

primes = [2, 3, 5, 7]

for i in range(8, 1000):
    prime = True
    for x in primes:
        if (i%x == 0):
            prime = False
    if prime:
        primes.append(i)

for i in range(0, tn):
    l = raw_input().split(' ')
    l = l[1:]
    for x in range(0, len(l)):
        try:
            l[x] = int(l[x])
        except:
            pass

    minmin = min(l)
    z = 0
    while(primes[z] <= minmin):
        divideAll = True
        for kk in l:
            if (kk%primes[z] != 0):
                divideAll = False
                break
        if (divideAll):
            for joca in range(0, len(l)):
                l[joca] = l[joca]/primes[z]
        else:
            z += 1
    for pipo in l:
        print(pipo, end=' ')
    print()
