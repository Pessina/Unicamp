n = raw_input()
skill = raw_input().split(' ')
for i in range(0, len(skill)):
    skill[i] = int(skill[i])
skill.sort()
problems = 0
for i in range(len(skill)-1, 0, -2):
    problems += skill[i] - skill [i-1]
print (problems)
