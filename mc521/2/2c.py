from __future__ import print_function

input = raw_input().split(' ')
n = int(input[0])
k = int(input[1])

ans = []
def pot_k (n, ans):
    pot = 2
    i = 0
    while pot**i <= n:
        i += 1
    res = n - pot**(i-1)
    if i != 0:
        ans.append(pot**(i-1))
    if res > 0:
        pot_k(res, ans)
    else:
        return ans

pot_k(n, ans)
if (len(ans) <= k):
    while(len(ans) < k):
        ans.sort()
        max = ans.pop()
        max = max/2
        ans.append(max)
        ans.append(max)
    ans.sort()
    if (ans[0] != 0):
        print('YES')
        for element in ans:
            print(element, end = ' ')
        print()
    else:
        print('NO')
else:
    print('NO')
