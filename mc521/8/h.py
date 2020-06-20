import math
from sys import stdin

checkTable = {}

def checkValue (coin):

    if (coin in checkTable):
        return checkTable[coin]

    coin1 = math.floor(coin/2)
    coin2 = math.floor(coin/3)
    coin3 = math.floor(coin/4)

    if (coin >= coin1 + coin2 + coin3):
        return coin

    else:
        x = checkValue (coin3) + checkValue (coin2) + checkValue (coin1)
        checkTable[coin] = x
        return x

while(True):
    try:
        i = input()
        print(int(checkValue(int(i))))
    except:
        break
