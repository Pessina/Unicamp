n = raw_input()
n = str(int(n) + 1)

while (len(set(n)) != 4):
    n = str(int(n) + 1)
print (n)
