import names
from random import randint

def generate_pessoa (cpf_set):
    cpf = randint(10000000000, 99999999999)
    if cpf not in cpf_set:
        cpf_set.add(cpf)
        sex = ['male', 'female'] [randint(0,1)]
        name = names.get_full_name(gender=sex)
        age = randint(1,100)
        pessoa = {
            'CPF':cpf,
            'primeiro_nome':name.split(' ')[0],
            'ultimo_nome':name.split(' ')[1],
            'sexo':sex,
            'idade': age
        }
        return pessoa
    return None

def generate_espectador(cpf):
    economica_condition = ['classe baixa', 'classe media', 'classe alta'] [randint(0,2)]
    region = ['sul', 'sudeste', 'nordeste', 'norte', 'centro oeste'] [randint(0,4)]
    politics_position = ['centro', 'direita', 'esquerda'] [randint(0,2)]
    religion = ['budista', 'catolico', 'espirita', 'judeu'] [randint(0,3)]

    espectador = {
        'CPF': cpf,
        'codicao_socioeconomica': economica_condition,
        'regiao_geografica': region,
        'posicao_politica': politics_position,
        'religiao': religion
    }
    return espectador

def generate_ator(cpf, horas_atuando, duble_cpf):
    ator = {
        'CPF': cpf,
        'horas_atuando': horas_atuando,
        'duble_cpf': duble_cpf,
        'seguidores_instagram': randint(0, 100000),
        'seguidores_twitter': randint(0, 100000)
    }
    return ator
