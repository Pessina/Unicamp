i = raw_input()
e = raw_input()

i = i.split(':')
e = e.split(':')

i[0] = int(i[0])
i[1] = int(i[1])
e[0] = int(e[0])
e[1] = int(e[1])

if (i[0] != e[0]):
    m = 60 - i[1] + e[1] + 60 * (e[0] - i[0] - 1)
    m = m/2
    h = m/60
    m = m%60
    x = i[1] + m
    if (x >= 60):
        h += 1
        x = x%60
    i[0] += h
    i[1] = x
else:
    m = e[1] - i[1]
    m = m/2
    i[1] += m

if (i[0] < 10):
    i[0] = '0' + str(i[0])
if (i[1] < 10):
    i[1] = '0' + str(i[1])
print(str(i[0]) + ':' + str(i[1]))
