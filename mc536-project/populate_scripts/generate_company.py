import names
import csv
from random import randint

def generate_empresa(cnpj_set, company_name, country_names):
    cnpj = randint(10000000000000, 99999999999999)
    if cnpj not in cnpj_set:
        cnpj_set.add(cnpj)
        tamanho_da_empresa = ['pequena', 'media', 'grande'] [randint(0,2)]
        pais_origem = (country_names [randint(0, len(country_names) - 1)])[1]
        company = {
            'CNPJ': cnpj,
            'nome': company_name.replace(',', ''),
            'tamanho_da_empresa': tamanho_da_empresa,
            'pais_origem': pais_origem.replace(',', '')
        }
        return company
    return None

def generate_emissora (cnpj):
    emissora = {
        'CNPJ': cnpj,
        'audiencia': randint(50, 5000)
    }
    return emissora

def generate_patrocinador(cnpj):
    ramo = ['alimentos', 'base', 'metalurgico', 'entretenimento', 'jogos', 'bebidas', 'agricultura', 'agropecuaria', 'tecnologia'] [randint(0, 8)]
    patrocinador = {
        'CNPJ': cnpj,
        'ramo': ramo
    }
    return patrocinador
