n = int(input())

def fibonacci(a):
    k = 0
    while(a[k] == 1 or a[k] == 2):
        print(1)
        k += 1

    i = 2
    x = z = 1
    while(len(a) != k):
        c = (x + z) % 100000007
        i += 1
        if i == a[k]:
            print(c)
            k += 1
        x = z
        z = c

a = []
for i in range(0, n):
    a.append(int(input()))
a.sort()
fibonacci(a)
