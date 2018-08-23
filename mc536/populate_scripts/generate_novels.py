import requests
import json
from random import randint
from random import randrange
from datetime import datetime
from datetime import timedelta

def api_request(release_date, page, index):
    base_url = 'https://api.themoviedb.org/3/discover/movie?api_key=59e68a6e68d3198ca64ed99809a2f14f'
    url = base_url + '&' + 'primary_release_year=' + str(release_date) + '&' + 'page=' + str(page)
    response = requests.get(url)
    json_data = json.loads(response.text)

    novel = json_data['results'][index]
    id_novel = novel['id']
    title_novel = novel['title']
    return (id_novel, title_novel)

def random_date():
    start = datetime.strptime('1/1/2000', '%m/%d/%Y')
    end = datetime.strptime('1/1/2017', '%m/%d/%Y')
    delta = end - start
    int_delta = (delta.days * 24 * 60 * 60) + delta.seconds
    random_second = randrange(int_delta)
    day = str(start + timedelta(seconds=random_second))[:10]
    hour = str(start + timedelta(seconds=random_second))[11:14] + '00:00'
    return(day,hour)

def generate_novela (diretor_cpf, release_date, page, index):
    id_novel, title_novel = api_request(release_date, page, index)
    day, hour = random_date()
    novela = {
        'ID': id_novel,
        'nome': title_novel,
        'numero_de_atores': randint(1, 100),
        'audiencia': randint(1000, 1000000),
        'diretor_cpf': diretor_cpf,
        'numero_de_episodios': randint(1, 100),
        'data_inicio': day,
        'horario': hour
    }
    return novela

def generate_duracao_novela(numero_de_episodios, data_inicio):
    duracao_novela = {
        'numero_de_episodios': numero_de_episodios,
        'data_inicio': str(data_inicio)[:10],
        'data_fim': str(data_inicio + timedelta(days=numero_de_episodios))[:10]
    }
    return duracao_novela

# Titulo e o nome de um filme
def generate_script(id_script_set, criador_cpf, titulo):
    id = randint(100000, 999999)
    if id not in id_script_set:
        id_script_set.add(id)
        tema = ['terror', 'drama', 'romance', 'policial', 'aventura', 'kids', 'musical', 'adulto', 'internacional'] [randint(0, 8)]
        script = {
            'ID': id,
            'titulo': titulo,
            'tema': tema,
            'criador_cpf': criador_cpf
        }
        return script
    return None











    #
