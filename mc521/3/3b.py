def insert(a, element, index):
    if len(a) == 1:
        if element > a[0]:
            return index + 1
        else:
            return index
    elif element > a[len(a)/2]:
        index = insert(a[(len(a)/2):], element, index + len(a)/2)
        return index
    else:
        index = insert(a[:(len(a)/2)], element, index)
        return index


n = raw_input()
a = raw_input().split(' ')
b = raw_input().split(' ')

for i in range (0, len(a)):
    a[i] = int(a[i])

for i in range (0, len(b)):
    b[i] = int(b[i])

for i in range(1, len(a)):
    a[i] = a[i] + a[i-1]

for element in b:
    x = insert(a, element, 0)
    if x == 0:
        print(str(0 + 1) + " " + str(element))
    else:
        print(str(x+1) + " " + str(element - a[x-1]))
