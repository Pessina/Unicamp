x = int(raw_input())

z = 0
y = []
while (x != 0):
    z += 1
    if (sum([int(i) for i in str(z)]) == 10):
        y.append(z)
        x -= 1

for i in range(0, len(y)-1):
    y[i] = y[i + 1] -y[i]
    if (y[i] != 9):
        print (y[i])

# print (y)
