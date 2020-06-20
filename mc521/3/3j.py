n = int(raw_input())
s = raw_input()
s = [c for c in s]

def remove_stone(s, i, x):
    if i == len(s):
        return x

    if s[i - 1] == s[i]:
        del s[i]
        x = remove_stone(s, i, x+1)
        return x
    else:
        x = remove_stone(s, i+1, x)
        return x

x = remove_stone(s, 1, 0)
print (x)
