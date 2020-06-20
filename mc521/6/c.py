while (True):
    n = int(input())
    if n == 0:
        break
    ages = input().split(' ')
    for i in range(0, len(ages)):
        ages[i] = int(ages[i])
    ages.sort()
    out = ""
    for element in ages:
        out += str(element) + " "
    print(out[:-1])
