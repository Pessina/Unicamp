import string

lines = int(raw_input())
input = []
for i in range(0, lines):
    line = raw_input().split(' ')
    aux = []
    aux.append(int(line[0]))
    aux.append(int(line[1]))
    input.append(aux)

alphabet = string.ascii_lowercase

for element in input:
    out = ""
    aux = 0
    for i in range(0, element[0]):
        out += alphabet[aux]
        aux += 1
        if aux > element [1] - 1:
            aux = 0
    print (out)
