-- Consultar todas as propriedades dos espectadores de uma novela:
select pessoa.cpf, pessoa.primeiro_nome, pessoa.ultimo_nome, pessoa.sexo, pessoa.idade from pessoa inner join (select * from assiste_a where id='322') as espectador_novela on pessoa.cpf = espectador_novela.cpf;

-- Consultar quais pessoas são os fãs de um dado ator:
select  pessoa.cpf, pessoa.primeiro_nome, pessoa.ultimo_nome, pessoa.sexo, pessoa.idade from pessoa inner join (select * from admira where ator_cpf = '85857930443') as fans_of on pessoa.cpf = espectador_cpf;

-- Dado uma empresa, qual o valor do anúncio:
select valor_anuncio.horario, valor_anuncio.duracao, valor_anuncio.valor from valor_anuncio inner join (select * from anuncia_em where anuncia_em.cnpj = '62749743857167') as anuncia_empresa on valor_anuncio.duracao = anuncia_empresa.duracao and valor_anuncio.horario = anuncia_empresa.horario;

-- Dado uma propriedade do espectador (CPF) consultar quais os autores dos scripts das novelas assistidas por ele:
select script.criador_cpf from script inner join (select * from tem inner join (select * from novela inner join (select id as id_assiste, cpf from assiste_a where cpf='73983644578') as novelas_assistidas_por on (novela.id = novelas_assistidas_por.id_assiste)) as ids_script_novela_assistida on (tem.novela_ID = ids_script_novela_assistida.id)) as scripts_das_novelas_assitidas on (script.id = scripts_das_novelas_assitidas.script_id);

-- Numero de espectadores por novela ordenados decrescente
select count(*) as num_espectadores, id from assiste_a group by id order by num_espectadores desc;

-- Dado uma novela, consultar quem são os seus espectadores espiritas.
select espectador.cpf as cpf_espiritas from espectador inner join ( select * from assiste_a where id='4614') as espectadores_novela on (espectador.cpf = espectadores_novela.cpf) where religiao='espirita';

-- Dado uma novela, consultar quantos espectadores de direita ela tem.
select count(*) as espectadores_direita from espectador inner join ( select * from assiste_a where id='4614') as espectadores_novela on (espectador.cpf = espectadores_novela.cpf) where posicao_politica='direita';

-- Dado uma novela, consultar quem são os espectadores menores de 18 anos ela tem.
select pessoa.cpf, pessoa.idade from pessoa inner join ( select * from assiste_a where id= '4614') as espectadores_novela on (pessoa.cpf = espectadores_novela.cpf) where idade<18 order by pessoa.idade asc;

-- Dado um ator, consultar qual o seu salário.
select valor as salario from salario inner join (select * from ator where cpf = '97910203555') as ator_selected on (ator_selected.horas_atuando = salario.horas_atuando);

-- Saber o número de atores por papel
select count(*), papel from participa group by papel;

-- Saber qual o ator mais popular no twitter
select ator.cpf, ator.seguidores_twitter from ator inner join pessoa on (ator.cpf=pessoa.cpf) order by seguidores_twitter desc limit 1;

-- Saber qual o ator mais popular no instagram
select ator.cpf, ator.seguidores_instagram from ator inner join pessoa on (ator.cpf=pessoa.cpf) order by seguidores_instagram desc limit 1;

-- Qual o ator com maior salário
select ator.cpf, salario.valor from ator inner join salario on (ator.horas_atuando = salario.horas_atuando) order by valor desc limit 1;

-- Procurar todos os filmes que começam com P
select novela.id, novela.nome from novela where nome like 'P%';

-- Consultar as pessoas mais novas do banco;
select pessoa.cpf, pessoa.idade from pessoa where pessoa.idade = (select min(pessoa.idade) from pessoa);

-- Consultar quantos homens existem no banco
select count(*) as num_homens from pessoa where sexo='male';

-- Consultar quantas mulheres existem agupadas por idade
select count(*) as num_mulheres, idade from pessoa where sexo='female' group by idade order by idade desc;

-- Consultar os scripts agrupados por tema
select count(*), tema from script group by tema;
