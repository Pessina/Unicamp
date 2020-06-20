n = raw_input().split(' ')
l = raw_input().split(' ')

number = int(n[0])
x = int(n[1])

for i in range(0, len(l)):
    l[i] = int(l[i])
l.sort()

while(len(l) > 1 and l[-1] + l[-2] > x):
    l.pop(-1)
    
print(len(l))
