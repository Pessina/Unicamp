n = int(input())

for i in range(0, n):
    strs = input().split(' ')
    for j in range(0, len(strs)):
        strs[j] = int(''.join(reversed(strs[j])))
    total = str(sum(strs))
    total = str(int(''.join(reversed(total))))
    print(total)
