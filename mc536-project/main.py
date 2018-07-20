import populate_scripts.generate_company as generate_company
import populate_scripts.generate_novels as generate_novels
import populate_scripts.generate_person as generate_person
import populate_scripts.generate_relations as generate_relations
import populate_scripts.constants_tables as constants_tables
import utils

import populate_scripts.constants as CONSTANTS

import copy

from random import randint
from datetime import datetime

salario_list = constants_tables.salario
valor_anuncio_list = constants_tables.valor_anuncio

length_salario = len(salario_list)
length_valor_anuncio = len(valor_anuncio_list)

pessoa_list = []
espectador_list = []
ator_list = []

cpf_set = set()

for i in range (0, 100000):
    pessoa = generate_person.generate_pessoa(cpf_set)
    if (pessoa != None):
        pessoa_list.append(pessoa)
        selector = randint(0, 10)
        if selector in [1, 2, 3, 4, 5, 6, 7]:
            espectador = generate_person.generate_espectador(pessoa['CPF'])
            espectador_list.append(espectador)
        if selector in [7, 8, 9]:
            duble_cpf = None
            if len(ator_list) > 0:
                duble_cpf = ator_list[randint(0, len(ator_list)-1)]['CPF']
                duble_cpf = [duble_cpf, duble_cpf, None] [randint(0, 2)]
            else:
                duble_cpf = None
            ator = generate_person.generate_ator (pessoa['CPF'], salario_list[randint(0, length_salario-1)]['horas_atuando'], duble_cpf)
            ator_list.append(ator)

novelas_list = []
script_list = []
duracao_novela_list = []

id_script_set = set()
duracao_novela_set = set()

for year in range (2000, 2005):
    for page in range (1, 5):
        for index in range(0, 4):
            novela = generate_novels.generate_novela(pessoa_list[randint(0, len(pessoa_list)-1)]['CPF'], year, page, index)
            duracao_novela = generate_novels.generate_duracao_novela (novela['numero_de_episodios'], datetime.strptime(novela['data_inicio'], '%Y-%m-%d'))
            script = generate_novels.generate_script(id_script_set, pessoa_list[randint(0, len(pessoa_list)-1)]['CPF'], novela['nome'])
            if (script != None):
                script_list.append(script)
            duracao_novela_list.append(duracao_novela)
            tupla_duracao_novela = (duracao_novela['numero_de_episodios'], duracao_novela['data_inicio'])
            if tupla_duracao_novela not in duracao_novela_set:
                duracao_novela_set.add(tupla_duracao_novela)
                novelas_list.append(novela)

empresa_list = []
patrocinador_list = []
emissora_list = []

cnpj_set = set()

counter = 0
while counter < len(CONSTANTS.COMPANIES):
    empresa = generate_company.generate_empresa(cnpj_set, CONSTANTS.COMPANIES[counter], CONSTANTS.COUNTRIES)
    if (empresa != None):
        empresa_list.append(empresa)
        selector = randint(0, 10)
        if selector in [1, 2, 3, 4]:
            patrocinador = generate_company.generate_patrocinador(empresa['CNPJ'])
            patrocinador_list.append(patrocinador)
        if selector in [4, 5]:
            emissora = generate_company.generate_emissora (empresa['CNPJ'])
            emissora_list.append(emissora)
        counter += 1

assiste_a_list = []
admira_list = []
participa_list = []
tem_list = []
paga_por_list = []
anuncia_em_list = []

assiste_a_set = set()
admira_set = set()
anuncia_em_set = set()

for i in range (0, int(len(pessoa_list)/2)):
    cpf = pessoa_list[randint (0, len(pessoa_list)-1)]['CPF']
    id = novelas_list[randint (0, len(novelas_list)-1)]['ID']
    tupla = (cpf, id)
    if (tupla not in assiste_a_set):
        assiste_a_set.add(tupla)
        assiste_a = generate_relations.generate_assiste_a (cpf, id)
        assiste_a_list.append(assiste_a)

for i in range (0, int(len(espectador_list)/2)):
    cpf_espectador = espectador_list[randint (0, len(espectador_list)-1)]['CPF']
    cpf_ator = ator_list[randint (0, len(ator_list)-1)]['CPF']
    tupla = (cpf_espectador, cpf_ator)
    if (tupla not in admira_set):
        admira_set.add(tupla)
        admira = generate_relations.generate_admira (cpf_espectador, cpf_ator)
        admira_list.append(admira)

for ator in ator_list:
    id = novelas_list[randint (0, len(novelas_list)-1)]['ID']
    participa = generate_relations.generate_participa (ator['CPF'], id)
    participa_list.append(participa)

for novela in novelas_list:
    for script in script_list:
        if (script['titulo'] == novela['nome']):
            tem = generate_relations.generate_tem (novela['ID'], script['ID'])
            tem_list.append(tem)

for ator in ator_list:
    cnpj = emissora_list [randint (0, len(emissora_list)-1)]['CNPJ']
    paga_por = generate_relations.generate_paga_por(ator['CPF'], cnpj)
    paga_por_list.append(paga_por)

for i in range (0, int(len(empresa_list)/3)):
    id = novelas_list[randint (0, len(novelas_list)-1)]['ID']
    cnpj = empresa_list [randint (0, len(empresa_list)-1)]['CNPJ']
    horario = constants_tables.valor_anuncio[randint(0, len(constants_tables.valor_anuncio)-1)]['horario']
    duracao = constants_tables.valor_anuncio[randint(0, len(constants_tables.valor_anuncio)-1)]['duracao']
    tupla = (id, cnpj)
    if (tupla not in anuncia_em_set):
        anuncia_em_set.add(tupla)
        anuncia_em = generate_relations.generate_anuncia_em (cnpj, id, horario, duracao)
        anuncia_em_list.append(anuncia_em)

lists = [{'value': salario_list, 'name': 'salario'},
        {'value': valor_anuncio_list, 'name': 'valor_anuncio'},
        {'value': pessoa_list, 'name': 'pessoa'},
        {'value': espectador_list, 'name': 'espectador'},
        {'value': ator_list, 'name': 'ator'},
        {'value': novelas_list, 'name': 'novela'},
        {'value': duracao_novela_list, 'name': 'duracao_novela'},
        {'value': script_list, 'name': 'script'},
        {'value': empresa_list, 'name': 'empresa'},
        {'value': patrocinador_list, 'name': 'patrocinador'},
        {'value': emissora_list, 'name': 'emissora'},
        {'value': admira_list, 'name': 'admira'},
        {'value': participa_list, 'name': 'participa'},
        {'value': tem_list, 'name': 'tem'},
        {'value': paga_por_list, 'name': 'paga_por'},
        {'value': assiste_a_list, 'name': 'assiste_a'},
        {'value': anuncia_em_list, 'name': 'anuncia_em'}]

for list in lists:
    utils.json_to_csv (list['value'], list['name'] + '.csv')

utils.create_populate_sql_script(lists)
