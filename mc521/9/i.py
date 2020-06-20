n = int(input())

dp = [(0, (0)), (1, (1))]

x = []
for i in range(0, n):
    x.append(int(input()))
x.sort()

while(len(x) != 0):
    for i in range(len(dp), x[0]):
        divres = False
        div = False
        new = False
        for x in range(1, len(dp)):
            if len(dp)%x == 0:
                div = dp[x][1]
                divres = len(dp)/x
                break
        if(divres):
            for z in range(0, len(dp)):
                if z == divres:
                    div += dp[z][1]
            new = (dp[len(dp) - 1] + sum(div), div)
        else:
            sett = fn(len(dp) + 1)
            new = (dp[len(dp) - 1] + sum(sett), sett)
        dp.append(new)

def fn(h):
    hset = set()
    for i in range(1, int(h/2)+1):
        if (h%i == 0):
            hset.add(i)
    return hset
