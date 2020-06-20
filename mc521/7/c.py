n = raw_input()
s = raw_input()
s = [i for i in s]

count = 0
for i in range(0, len(s), 2):
    if s[i] == s[i+1]:
        count += 1
        if s[i] == 'a':
            s[i] = 'b'
        else:
            s[i] = 'a'

print (count)
print (''.join(s))
