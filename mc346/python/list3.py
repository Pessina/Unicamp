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

class Info:
    def __init__ (self, f):
        self.f = f
        self.info = ""

    def __call__(self, *args):
        x = f(*args)
        self.info = "Calling {0}, Arguments = {1}, Time = {2}, Return = {3}".format(f.__name__, args, datetime.now(), x)
        print (self.info)
        return x

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

x = Info(f)

print (x(5, 10))
