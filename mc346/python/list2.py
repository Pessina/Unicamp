# pares: dado um iterator, retorna um iterator com os elementos nas posicoes pares (0,2)
def pares(iterator):
    return pares_2(iterator, 0)

def pares_2(iterator, i):
    x = next(iterator, None)
    if (x):
        lista = list(pares_2(iterator, 1 if i == 0 else 0))
        if (i == 0):
            lista.insert(0, x)
        return iter(lista)
    else:
        return iter([])

# reverte: dado um iterator, reverte ele *
def reverte(iterator):
    x = next(iterator, None)
    if (x):
        lista = list(reverse(iterator))
        lista.append(x)
        return iter(lista)
    else:
        return iter([])


# zip: dado 2 iterators, retorna um iterator que retorna os elementos intercalados
def zip(iterator1, iterator2):
    return zip_2(iterator1, iterator2, 0)

def zip_2(iterator1, iterator2, i):
    x = None
    if i == 0:
        x = next(iterator1, None)
    if i == 1:
        x = next(iterator2, None)
    if (x):
        lista = list(zip_2(iterator1, iterator2, 1 if i == 0 else 0))
        lista.insert(0, x)
        return iter(lista)
    else:
        return iter([])

def cart(iterator1, iterator2):
    while True:
        yield next(iterator1) * next(iterator2)

def ciclo(iterator):
    lista = list(iterator)
    while True:
        x = next(iterator, None)
        if x:
            yield x
        else:
            iterator = iter(lista)

def rangeinf(init, passo):
    i = 0
    while True:
        yield init + i * passo
        i = i + 1

def take(lista, n):
    return lista[:n]

def drop(list, n):
    return lista[n:]
