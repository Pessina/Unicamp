n = raw_input()
s = raw_input()
vowels = ['a', 'e', 'i', 'o', 'u', 'y']

i = 0
while i < len(s) - 1:
    if s[i] in vowels and s[i+1] in vowels:
        s = s[:i+1] + s[i+2:]
        continue
    i += 1
print (s)
