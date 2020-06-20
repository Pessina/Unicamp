input = raw_input().split(' ')
n = int(input[0])
t = int(input[1])
cells = raw_input().split(' ')

for i in range(0, len(cells)):
    cells[i] = int(cells[i])

pos = 1
caminhos =[]
caminhos.append(pos)
while (pos < n):
    pos = cells[pos - 1] + pos
    caminhos.append(pos)
if(t in caminhos):
    print('YES')
else:
    print('NO')
