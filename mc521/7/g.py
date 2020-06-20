x = int(raw_input())

for i in range(0, x):
    n = int(raw_input())
    count = 0
    while (n != 1):
        if (n%2==0):
            count += 1
            n = n/2
            continue
        if (n%3==0):
            count += 1
            n = 2*n/3
            continue
        if (n%5==0):
            count += 1
            n = 4*n/5
            continue
        else:
            count = -2
            break
    if (count == -2):
        print (-1)
    else:
        print(count)
