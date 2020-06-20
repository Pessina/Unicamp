n = raw_input()
flat = raw_input().split(' ')
for i in range(0, len(flat)):
    flat[i] = int(flat[i])

count = 0
for i in range(1, len(flat) - 1):
    if (flat[i] == 0):
        if (flat[i-1]==1 and flat[i+1]==1):
            flat[i + 1 ] = -1
            count += 1
print (count)
