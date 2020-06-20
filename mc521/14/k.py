x = int(input())

for i in range(0, x):
    y = int(input())
    possible = True
    max_p = -1
    max_c = -1
    for j in range(0, y):
        a = input().split(' ')
        p = int(a[0])
        c = int(a[1])
        change_p = False
        change_c = False

        # Plays decrease
        if (p > max_p):
            change_p_value = p - max_p
            max_p = p
            change_p = True
            
        elif (p < max_p):
            possible = False

        # Clear decrease
        if (c > max_c):
            change_c_value =  c - max_c
            max_c = c
            change_c = True
        elif(c < max_c):
            possible = False

        # Clear change but plays dont
        if (change_c == True and change_p == False):
            possible = False
        
        # Change on c should be not greater on p
        if (change_c == True and change_p == True):
            if (change_c_value > change_p_value):
                possible = False

        # More clear than plays
        if (c > p):
            possible = False

    if(possible):
        print('YES')
    else:
        print('NO')