import math

def f (x):
    return x**3.0 - 9.0*x + 3.0

def bisection(a, b, error, f, iter):
    i = 0
    while i < iter:

        x = (b + a)/2.0
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

print (bisection(0.0, 1.0, 10**-5, f, 10))
