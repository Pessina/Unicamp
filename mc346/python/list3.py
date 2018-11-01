import time
from datetime import datetime

def decorator_time(f):
    def wrapper_time(*args):

        time_begin = datetime.now()
        x = f(*args)
        time_end = datetime.now()

        print ((time_end - time_begin).total_seconds())
        return x

    return wrapper_time

def decorator_info (f):

    def wrapper_info (*args):

        print ("Calling {0} with Arguments = {1}, time = {2}".format(f.__name__, args, datetime.now()))
        x = f(*args)
        print ("Return = {0}".format(x))

        return x
    return wrapper_info

class Memorize:
    def __init__ (self, f):
        self.dict_mem = {}
        self.f = f

    def __call__ (self, *args):
         try:
             x = self.dict_mem[args]
             print ('hit dict')
             return x
         except:
             print ('miss dict')
             x = self.f(*args)
             self.dict_mem[args] = x
             return x

def decorator_log(f, arq):
    def wrapper_log(*args):
        with open(arq, 'a') as arq_open:
            arq_open.write("Calling {0} with Arguments = {1}, time = {2}\n".format(f.__name__, args, datetime.now()))
            x = f(*args)
            return x
    return wrapper_log

def f (x, y):
    return x * y

x = Memorize(f)

print (x(5, 10))
print (x(5, 10))
print (x(10, 10))
print (x(5, 10))
print (x(10, 10))
