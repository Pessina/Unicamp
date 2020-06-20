n = int(input())

for i in range(0, n):
    t = int(input())
    if t%2 == 0:
        print(int(t/2 - 1))
    else:
        print(int(t/2))
