a = int(raw_input())

for i in range(0, a):
    x = int(raw_input())
    sum = 3
    i = 2
    while(x%sum != 0):
        sum += 2**i
        i += 1
    print(x/sum)
