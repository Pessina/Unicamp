a = int(input())

for i in range(0, a):
    x = int(input())
    sum = 3
    i = 2
    while(x%sum != 0):
        sum += 2**i
        i += 1
    print(int(x/sum))
