n = int(raw_input())
s = raw_input()

a = {}
for i in range(1, len(s)):
    if str(s[i-1] + s[i]) in a:
        a [str(s[i-1] + s[i])] += 1
    else:
        a [str(s[i-1] + s[i])] = 1
max_key = max(a, key=a.get)
print (max_key)
