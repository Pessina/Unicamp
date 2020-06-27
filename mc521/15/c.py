al = ['b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
pot = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432]
def s(x):
    x = chr(x)
    if x == 'a':
        return 'a'
    else:
        return s(ord(x) - 1) + x + s(ord(x) -1)

n = int(input())
for i in range(len(pot)-1, -1, -1):
    if (n % 2 == 1):
        print('a')
        break
    elif ((n) % pot[i] == 0):
        print(al[i])
        break
    
