#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String [50];

//Estrutura para os elementos da tabela hash
typedef struct elementoTabela
{
	struct elementoTabela *palavraAnterior;
	String palavra;
	struct elementoTabela *palavraSeguinte;
	struct elementoTabela *prox;
}elementoTabela;

//Listas de string
typedef struct elementoListaString
{
	String palavra;
	struct elementoListaString *prox;
}elementoListaString;

//Elemento para o vetor de jogadores
typedef struct elementoJogador
{
	int flagRodada;
	int pontos;
}elementoJogador;

//Retorna a posição na tabela hasg
int Hash (char *str, int numeroPalavras);
//Insere o elemento na tabela hash
void InsereTabela (elementoTabela *elementoNovo, elementoTabela **tabelaHash, int posicaoTabela);
//Cria uma lista de Strings
elementoListaString *CriaLista (elementoListaString *inicio, int numeroPalavrasFrase);
//Dada uma frase do texto, ele verifica a partir da ultima palavra da frase. Para cada palavra da lista da tabela Hash, qual delas, esta inserida no contexto da frase
int VerificaTabela (elementoTabela *tabelaHash, elementoListaString *listaString);
//Libera memoria
void freeLista (elementoListaString *inicio);
void freeListaTabela (elementoTabela *inicio);

int main (int argc, char const *argv[])
{
	int numeroPalavras, posicaoTabela;
	elementoTabela **tabelaHash;
	String palavra;

	scanf ("%d", &numeroPalavras);
	//Cria e inicializa a tabela hash
	tabelaHash = (elementoTabela **) malloc (numeroPalavras * sizeof (elementoTabela*));
	for (int i = 0; i<numeroPalavras; i++) 
		tabelaHash [i] = NULL;

	//Cria uma lista ligada com o texto, e insere os elementos na tabela hash
	for (int i = 0; i<numeroPalavras; i++) 
	{
		elementoTabela *elementoNovo, *elementoAnterior;
		scanf ("%s", palavra);
		if (i == 0) 
		{
			elementoNovo = (elementoTabela *) malloc (sizeof (elementoTabela));
			strcpy (elementoNovo->palavra, palavra);
			elementoNovo->palavraAnterior = NULL;
			elementoNovo->palavraSeguinte = NULL;
			elementoNovo->prox = NULL;
			elementoAnterior = elementoNovo;
		}
		else
		{
			elementoNovo = (elementoTabela *) malloc (sizeof (elementoTabela));
			strcpy (elementoNovo->palavra, palavra);
			elementoNovo->palavraAnterior = elementoAnterior;
			elementoNovo->palavraSeguinte = NULL;
			elementoNovo->prox = NULL;
			elementoAnterior->palavraSeguinte = elementoNovo;
			elementoAnterior = elementoNovo;
		}
		posicaoTabela = Hash (palavra, numeroPalavras);
		InsereTabela (elementoNovo, tabelaHash, posicaoTabela);
	}

	int numeroRodadas, numeroJogadores, numeroPalavrasFrase;
	elementoJogador *listaJogadores;

	//Cria e inicizaliza o vetor de jogadores
	scanf ("%d %d", &numeroRodadas, &numeroJogadores);
	listaJogadores = (elementoJogador *) malloc (numeroJogadores * sizeof (elementoJogador));
	for (int j = 0; j<numeroJogadores; j++) {
		listaJogadores [j].pontos = 0;
		listaJogadores [j].flagRodada = 0;
	}

	//Realiza a troca de rodadas, le a frase da rodada e os palpites de cada jogador. Criando uma lista ligada para a frase e outra para os palpites
	for (int i = 0; i<numeroRodadas; i++)
	{
		scanf ("%d", &numeroPalavrasFrase);
		elementoListaString *inicio = NULL;
		elementoTabela *inicioTabela = NULL;
		elementoListaString *inicioPalavrasJogadores = NULL;
		//Indica se um dos jogadores acertou a palavra na rodada
		int flagRodada = 0;
		int palavrasPosFraseRodada;

		inicio = CriaLista (inicio, numeroPalavrasFrase);
		inicioPalavrasJogadores = CriaLista (inicioPalavrasJogadores, numeroJogadores);
		posicaoTabela = Hash (inicio->palavra, numeroPalavras);
		inicioTabela = tabelaHash [posicaoTabela];
		//Percorre a lista ligada, associada a uma posição da tabela hash, testando para cada palabra da lista, se ela se encaixa na frase da rodada
		while (inicioTabela != NULL) {
			int verificaRetorno;
			elementoListaString *inicioListaString = inicio;
			elementoListaString *inicioPalavrasJogadoresFinal = inicioPalavrasJogadores;

			verificaRetorno = VerificaTabela (inicioTabela, inicioListaString);

			//Se a palavra se encaixa, compara-se o palpite de cada jogador com a palavra seguinte
			if (verificaRetorno == 1) 
			{
				for (int j = numeroJogadores-1; j>=0; j--) 
				{
					if (strcmp (inicioPalavrasJogadoresFinal->palavra, inicioTabela->palavraSeguinte->palavra)==0)
					{
						flagRodada = 1;
						listaJogadores [j].pontos += 100;
						listaJogadores [j].flagRodada = 1;
					}
					if (inicioPalavrasJogadoresFinal->prox != NULL)
						inicioPalavrasJogadoresFinal = inicioPalavrasJogadoresFinal->prox; 
				}
			if (inicioTabela->palavraSeguinte != NULL)
				palavrasPosFraseRodada += 10;
			}
			inicioTabela = inicioTabela->prox; 
		}
		//Se algum jogador ganhou, atualiza as flags dos jogdaores, e os pontos dos jogadores que perderam
		if (flagRodada != 0)
		{
			for (int j = 0; j<numeroJogadores; j++) 
			{
				if (listaJogadores [j].flagRodada == 0) 
				{
					listaJogadores [j].pontos -= palavrasPosFraseRodada;
					if (listaJogadores [j].pontos < 0)
						listaJogadores [j].pontos = 0;
				}
				listaJogadores [j].flagRodada = 0;
			}
		}
		flagRodada = palavrasPosFraseRodada = 0;
		//Imprime a saida
		if (i >= 9)
			printf("Rodada %2d:", i+1);
		else
			printf("Rodada%2d:", i+1);
		for (int j = 0; j<numeroJogadores; j++)
			printf(" %4d", listaJogadores [j].pontos);
		printf("\n");
		//Libera a memoria das listas da rodada
		freeLista (inicio);
		freeLista (inicioPalavrasJogadores);
	}

	//Libera a memoria do programa
	free (listaJogadores);
	for (int i = 0; i<numeroPalavras; i++)
		freeListaTabela (tabelaHash [i]);

	return 0;
}

int Hash (char *str, int numeroPalavras)
{
    int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    hash = hash&numeroPalavras;

    return hash;
}

void InsereTabela (elementoTabela *elementoNovo, elementoTabela **tabelaHash, int posicaoTabela) 
{
	elementoTabela *auxiliarTroca = tabelaHash [posicaoTabela];

	tabelaHash [posicaoTabela] = elementoNovo;
	elementoNovo->prox = auxiliarTroca;

	return;
}

elementoListaString *CriaLista (elementoListaString *inicio, int numeroPalavrasFrase) 
{
	elementoListaString *elementoNovo, *auxiliarTroca;

	for (int i = 0; i<numeroPalavrasFrase; i++) {
		String palavra;
		elementoNovo = (elementoListaString *) malloc (sizeof (elementoListaString));
		scanf ("%s", palavra);
		strcpy (elementoNovo->palavra, palavra);
		elementoNovo->prox = NULL;
		auxiliarTroca = inicio;
		inicio = elementoNovo;
		elementoNovo->prox = auxiliarTroca;
	}

	return inicio;
}

int VerificaTabela (elementoTabela *tabelaHash, elementoListaString *listaString)
{

	while (listaString != NULL) 
	{
		if (strcmp (listaString->palavra, tabelaHash->palavra) != 0)
			return 0;
		tabelaHash = tabelaHash->palavraAnterior;
		listaString = listaString->prox;
	}

	return 1;
}

void freeLista (elementoListaString *inicio)
{
	elementoListaString *auxiliarFree = inicio;

	while (inicio != NULL)
	{
		inicio = inicio->prox;
		free (auxiliarFree);
		auxiliarFree = inicio;
	}

	return;
}

void freeListaTabela (elementoTabela *inicio)
{
	elementoTabela *auxiliarFree = inicio;

	while (inicio != NULL)
	{
		inicio = inicio->prox;
		if (inicio != NULL) 
		{
			free (auxiliarFree);
			auxiliarFree = inicio;
		}
	}

	return;
}






