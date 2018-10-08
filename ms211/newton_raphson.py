import math

def f (x):
    return 10-1/x

def df (x):
    return 1/x**2

def newton_raphson (x1, f, df, error, iter):
    i = 0

    while i < iter:
        if abs (f(x1)) < error:
            break

        x2 = x1 - f(x1)/df(x1)
        print (x2)

        if abs (x1 - x2) < error:
            x1 = x2
            break

        x1 = x2
        i = i + 1

    return x1

print (newton_raphson(3.0/21.0, f, df, 10**-4, 100))
