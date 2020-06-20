n = int(raw_input())

database = {}
for i in range(0, n):
    name = raw_input()
    append = 1
    if name not in database:
        database[name] = 0
        print ('OK')
    else:
        print(name + str(database[name] + 1))
        database[name] += 1
