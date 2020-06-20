n = raw_input()
s = raw_input().split(' ')

for i in range(0, len(s)):
    s[i] = int(s[i])

max = 0
current = 1
for i in range(1, len(s)):
    if (s[i] >= s[i-1]):
        current += 1
    else:
        if current > max:
            max = current
        current = 1

if current > max:
    max = current
current = 0

print(max)
