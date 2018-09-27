import math

def f (x):
    return x**3.0 - 27

def bisection(a, b, error, f, iter):
    i = 0
    while i < iter:

        x = (b * abs(f(a)) + a * abs(f(b)))/(abs(f(a)) + abs(f(b)))
        print (str(x) + "   " + str(f(x)) + "\n")

        if abs(f(x)) < error:
            break

        if (f(x) * f(a) > 0):
            a = x
        else:
            b = x

        if abs(b-a) < error:
            break


        i = i + 1
    return x

print (bisection(0.0, 4.0, 10**-5, f, 10))
