from random import randint

def generate_assiste_a (cpf, id):
    assiste_a = {
        'CPF':cpf,
        'ID':id
    }
    return assiste_a

def generate_admira (cpf_pessoa, cpf_ator):
    admira = {
        'pessoa_CPF': cpf_pessoa,
        'ator_CPF': cpf_ator
        }
    return admira

def generate_participa (cpf, id):
    papel = ['figurante', 'mochinho', 'mocinha', 'heroi', 'ladrao', 'assassino', 'lenhador', 'banqueiro'] [randint(0, 7)]

    participa =  {
        'CPF':cpf,
        'ID': id,
        'papel': papel
    }
    return participa

def generate_tem (id_novela, id_script):
    tem = {
        'novela_ID':id_novela,
        'script_ID': id_script
    }
    return tem

def generate_paga_por(cpf, cnpj):
    paga_por = {
        'CNPJ': cnpj,
        'CPF': cpf
    }
    return paga_por

def generate_anuncia_em (cnpj, id, horario, duracao):
    produto_anunciado = ['cerveja', 'carro', 'remedio', 'brinquedo', 'alimento', 'evento'] [randint(0, 5)]

    anuncia_em = {
        'CNPJ': cnpj,
        'ID': id,
        'produto_anunciado': produto_anunciado,
        'horario': horario,
        'duracao': duracao
    }
    return anuncia_em
