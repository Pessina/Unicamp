def f (x):
    return x**3.0 - 9 * x + 3

def df (x):
    return 3.0*x**2 - 9

def newton_raphson (x1, f, df, error, iter):
    i = 0

    while i < iter:
        if abs (f(x1)) < error:
            break

        x2 = x1 - f(x1)/df(x1)

        if abs (x1 - x2) < error:
            x1 = x2
            break

        x1 = x2
        i = i + 1

    return x1

print (newton_raphson(0.5, f, df, 10**-5, 2))
