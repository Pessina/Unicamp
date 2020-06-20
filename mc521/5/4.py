n = raw_input()
e1 = raw_input().split(' ')
e2 = raw_input().split(' ')
e3 = raw_input().split(' ')

e1.sort()
e2.sort()
e3.sort()

def check_list(list1, list2):
    for element in list2:
        list1.remove(element)
    print(list1[0])

check_list(e1, e2)
check_list(e2, e3)
