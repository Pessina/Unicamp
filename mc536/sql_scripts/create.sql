-- Script to create tables
-- psql -d joker -a -f create.sql

CREATE TABLE pessoa (
    CPF varchar(11) PRIMARY KEY,
    primeiro_nome varchar(100),
    ultimo_nome varchar(100),
    sexo varchar(6), --change from 1 to 6 char, to use male and female
    idade int
);

CREATE TABLE espectador (
    CPF varchar(11) PRIMARY KEY REFERENCES pessoa,
    condicao_socioeconomica varchar(50),
    regiao_geografica varchar(50),
    posicao_politica varchar(50),
    religiao varchar(50)
);

CREATE TABLE salario (
    horas_atuando int PRIMARY KEY,
    valor decimal(5) -- change from 2 to 5 digits
);

CREATE TABLE ator (
    CPF varchar(11) PRIMARY KEY REFERENCES pessoa,
    horas_atuando int REFERENCES salario,
    duble_cpf varchar(11) REFERENCES ator(CPF),
    seguidores_instagram int,
    seguidores_twitter int
);

CREATE TABLE novela (
    ID int PRIMARY KEY,
    nome varchar(100),
    numero_de_atores int,
    audiencia int,
    diretor_cpf varchar(11) REFERENCES pessoa(CPF),
    numero_de_episodios int,
    data_inicio date,
    horario time
);

CREATE TABLE duracao_novela (
    numero_de_episodios int,
    data_inicio date,
    data_fim date,
    PRIMARY KEY (numero_de_episodios, data_inicio)
);

CREATE TABLE script (
    ID int PRIMARY KEY,
    titulo varchar(100),
    tema varchar(30), -- change from 10 to 30
    criador_cpf varchar(11) REFERENCES pessoa(CPF)
);

CREATE TABLE empresa (
    CNPJ varchar(14) PRIMARY KEY,
    nome varchar(100),
    tamanho_da_empresa varchar(10),
    pais_origem varchar(100)
);

CREATE TABLE emissora (
    CNPJ varchar(14) PRIMARY KEY REFERENCES empresa,
    audiencia int
);

CREATE TABLE patrocinador (
    CNPJ varchar(14) PRIMARY KEY REFERENCES empresa,
    ramo varchar(50)
);

CREATE TABLE assiste_a (
    CPF varchar(11) REFERENCES pessoa,
    ID int REFERENCES novela,
    PRIMARY KEY (CPF, ID)
);

CREATE TABLE admira (
    espectador_CPF varchar(11) REFERENCES espectador(CPF),
    ator_CPF varchar(11) REFERENCES ator(CPF),
    PRIMARY KEY (espectador_CPF, ator_CPF)
);

CREATE TABLE participa (
    CPF varchar(11) REFERENCES ator,
    ID int REFERENCES novela,
    papel varchar(50),
    PRIMARY KEY(CPF, ID)
);

CREATE TABLE tem (
    novela_ID int REFERENCES novela(ID),
    script_ID int REFERENCES script(ID),
    PRIMARY KEY(novela_ID, script_ID)
);

CREATE TABLE paga_por (
    CNPJ varchar(14) REFERENCES emissora,
    CPF varchar(11) REFERENCES ator,
    PRIMARY KEY (CNPJ, CPF)
);

CREATE TABLE anuncia_em (
    CNPJ varchar(14) REFERENCES empresa,
    ID int REFERENCES novela,
    produto_anunciado varchar(50),
    horario time,
    duracao time, -- change from int to time
    PRIMARY KEY (CNPJ,ID)
);

CREATE TABLE valor_anuncio (
  	horario time,
  	duracao time,
    valor  decimal(6), -- change from 2 to 6
    PRIMARY KEY (horario, duracao, valor)
);
