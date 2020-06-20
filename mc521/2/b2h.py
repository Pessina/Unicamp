n = int(raw_input())
for i in range(0, n):
    aux1 = raw_input().split(' ')
    max = int(aux1[1])
    aux2 = raw_input().split(' ')
    for z in range(0, len(aux2)):
        aux2[z] = int(aux2[z])
    student1 = aux2[0]
    aux2[0] = 0
    ans = sum(aux2)
    while (student1 < max and ans > 0):
        student1 += 1
        ans -= 1
    print(student1)
