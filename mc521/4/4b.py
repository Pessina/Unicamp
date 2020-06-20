s = int(raw_input().split(' ')[1])
b = raw_input().split(' ')

minimo = 3123213
for i in range(0, len(b)):
    b[i] = int(b[i])
    if s % b[i] == 0:
        if s/b[i] < minimo:
             minimo = s/b[i]
print(minimo)
