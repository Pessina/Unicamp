n = int(raw_input())
s = raw_input()

a = 0
b = {
    '0' : 0
}

for i in range(0, len(s)):
    if s[i] == 'x':
        b[str(a)] += 1
    else:
        a += 1
        b [str(a)] = 0

sum = 0
for i in range (0, a+1):
    if b[str(i)] > 2:
        sum += b[str(i)] - 2
print (sum)
