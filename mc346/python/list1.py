def par_lista(lista):
 return [x for x in lista if x % 2 == 0]

def index_par(lista):
    lista2 = []
    for i in range(0, len(lista)):
        if i % 2 == 0:
            lista2.append(lista[i])
    return lista2

def contar_list(lista):
    dicionario = {}
    for element in lista:
        if element in dicionario:
            dicionario [element] = dicionario [element] + 1
        else:
            dicionario [element] = 1
    return dicionario

def maior_valor(dicionario):
    key = None
    maxValue = float("-inf")
    for k, v in dicionario.items():
        if v > maxValue:
            key = k
            maxValue = v
    return key

def mais_comum (lista):
    return maior_valor(contar_list(lista))

def sublista(lista1, lista2):
    for element in lista2:
        if element not in lista1:
            return False
        lista1.remove(element)
    return True

def fim_igual_comeco(lista1, lista2):
    return lista1[-4:] == lista2 [:4]
