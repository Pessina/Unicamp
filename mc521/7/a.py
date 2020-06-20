x = raw_input().split(' ')
n = int(x[0])
v = [int(x[1]), int(x[2]), int(x[3])]
v.sort()

def cut_ribbon(n, v):
    if (n- v[0] >= v[0]):
        return cut_ribbon(n - v[0], v) + cut_ribbon(v[0], v)
    if (n- v[1] >= v[0]):
        return cut_ribbon(n - v[1], v) + cut_ribbon(v[1], v)
    if (n- v[2] >= v[0]):
        return cut_ribbon(n - v[2], v) + cut_ribbon(v[2], v)
    else:
        return 1

print (cut_ribbon(n, v))
