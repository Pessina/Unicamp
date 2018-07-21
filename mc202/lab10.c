#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String [50];
typedef struct listaString
{
	String palavra;
	struct listaString *prox;
}listaString;
typedef struct vertice
{
	String palavra;
	struct aresta *proxAresta;
	unsigned long int distancia;
	struct vertice *pai;
	int indice;
	int verificador;
}vertice;
typedef struct aresta
{
	int peso;
	struct vertice *pointVertice;
	struct aresta *proxAresta;
}aresta;

void BuscaLargura (vertice *vetorPalavras, String palavraInicio, String palavraFim, int numeroPalavrasDistintas);
void Troca (vertice *vetorPalavrasHeap, int posicao1, int posicao2);
int EncontraMinimo (vertice *vetorPalavrasHeap, int numeroPalavrasDistintas);

int main(void)
{
	int numeroPalavrasDistintas, M, numeroFrases;
	vertice *vetorPalavras;

	scanf ("%d %d %d", &numeroPalavrasDistintas, &M, &numeroFrases);

	//Cria a inicializa o vetor com as palavras
	vetorPalavras = (vertice *) malloc (sizeof (vertice) * numeroPalavrasDistintas);
	for (int i = 0; i<numeroPalavrasDistintas; i++)
	{
		vetorPalavras [i].palavra [0] = '0';
		vetorPalavras [i].indice = i;
	}

	for (int i = 0; i<numeroFrases; i++) 
	{
		int numeroPalavrasFrase;
		int zAnterior = 0;

		scanf ("%d", &numeroPalavrasFrase);
		for (int j = 0; j<numeroPalavrasFrase; j++) 
		{
			String palavra;
			int z = 0;
			int verificador = 0;

			scanf ("%s", palavra);
			while (vetorPalavras [z].palavra [0] != '0') 
			{
				//A palavra lida ja esta no vetor
				if (strcmp (vetorPalavras [z].palavra, palavra) == 0)
				{
					verificador = 1;
					break;
				}
				z++;
			}
			if (verificador == 0) 
			{
				strcpy (vetorPalavras [z].palavra, palavra);
				vetorPalavras [z].proxAresta = NULL;
			}

			//Não pode ser a primeira palavra de uma frase
			if (j != 0) 
			{
				aresta *auxiliarPercorreLista = vetorPalavras [zAnterior].proxAresta;
				verificador = 0;

				//Percorre a lista de palavras, se encontrar, atualiza o M
				while (auxiliarPercorreLista != NULL) 
				{
					//Palavra procurada ja esta na lista, atualiza o M
					if (strcmp (palavra, auxiliarPercorreLista->pointVertice->palavra) == 0)
					{
						auxiliarPercorreLista->peso--;
						verificador = 1;
						break;
					}
					auxiliarPercorreLista = auxiliarPercorreLista->proxAresta;
				}
				aresta *auxiliar;

				//Caso a palavra não esteja na lista, cria-se um novo elemento
				if (verificador == 0)
				{
					auxiliar = vetorPalavras [zAnterior].proxAresta;
					vetorPalavras [zAnterior].proxAresta = (aresta *) malloc (sizeof (aresta));
					vetorPalavras [zAnterior].proxAresta->peso = M-1;
					vetorPalavras [zAnterior].proxAresta->proxAresta = auxiliar;
					vetorPalavras [zAnterior].proxAresta->pointVertice = &vetorPalavras [z];
				}
			}
			zAnterior = z;
		}
	}

	int numeroFrasesCompletar;

	scanf ("%d", &numeroFrasesCompletar);

	//Le duas palavras e monta a frase
	for (int i = 0; i<numeroFrasesCompletar; i++) 
	{
		String palavraInicio, palavraFim;

		scanf ("%s %s", palavraInicio, palavraFim);
		BuscaLargura (vetorPalavras, palavraInicio, palavraFim, numeroPalavrasDistintas);
	}



	//Libera a Memoria
	for (int i = 0; i<numeroPalavrasDistintas; i++) 
	{
		aresta *auxiliarPercorreLista = vetorPalavras [i].proxAresta;
		while (auxiliarPercorreLista != NULL) 
		{
			aresta *auxiliarRemove = auxiliarPercorreLista;
			auxiliarPercorreLista = auxiliarPercorreLista->proxAresta;
			free (auxiliarRemove);
		}
	}
	free (vetorPalavras);




	return 0;
}

void BuscaLargura (vertice *vetorPalavras, String palavraInicio, String palavraFim, int numeroPalavrasDistintas) 
{

	vertice *vetorPalavrasHeap;
	int indiceInicio, indiceFim;

	//Vetor com referencia ao grafo através dos indices
	vetorPalavrasHeap = (vertice *) malloc (sizeof (vertice) * numeroPalavrasDistintas);

	for (int i = 0; i < numeroPalavrasDistintas; i++) 
	{
		vetorPalavrasHeap [i].indice = i;
		vetorPalavrasHeap [i].distancia = 4000000000;
		vetorPalavrasHeap [i].pai = NULL;
		if (strcmp (vetorPalavras [i].palavra, palavraInicio) == 0)
		{
			indiceInicio = i;
			vetorPalavrasHeap [i].distancia = 0;
		}
		if (strcmp (vetorPalavras [i].palavra, palavraFim) == 0)
		{
			indiceFim = i;
		}
	}

	int indiceMinimo;
	//Algoritmo de Dijkstra
	for (int i = 0; i<numeroPalavrasDistintas; i++) 
	{
		//Encontra a menor distancia do vetor
		indiceMinimo = EncontraMinimo (vetorPalavrasHeap, numeroPalavrasDistintas);
		vetorPalavrasHeap [indiceMinimo].verificador = -1;

		aresta *auxiliarPercorreLista = vetorPalavras [indiceMinimo].proxAresta;
		while (auxiliarPercorreLista != NULL)
		{
			if (vetorPalavrasHeap [auxiliarPercorreLista->pointVertice->indice].distancia > auxiliarPercorreLista->peso + vetorPalavrasHeap [indiceMinimo].distancia)
			{
				vetorPalavrasHeap [auxiliarPercorreLista->pointVertice->indice].distancia = auxiliarPercorreLista->peso + vetorPalavrasHeap [indiceMinimo].distancia;
				vetorPalavrasHeap [auxiliarPercorreLista->pointVertice->indice].pai = &vetorPalavrasHeap [indiceMinimo];
			}
			auxiliarPercorreLista = auxiliarPercorreLista->proxAresta;
		}
	}

	//Diz se a Frase existe ou não
	int verificaFrase = 1;
	listaString *inicio, *novoElemento;
	inicio = NULL;

	//Cria uma nova lista, com a frase a ser printada
	novoElemento = (listaString *) malloc (sizeof (listaString));
	strcpy (novoElemento->palavra, vetorPalavras [indiceFim].palavra);
	novoElemento->prox = inicio;
	inicio = novoElemento;

	vertice *auxiliar = &vetorPalavrasHeap [indiceFim];
	while (auxiliar != &vetorPalavrasHeap [indiceInicio]) {
		if (auxiliar->pai == NULL)
		{
			verificaFrase = 0;
			printf("erro");
			break;	
		}

		novoElemento = (listaString *) malloc (sizeof (listaString));
		strcpy (novoElemento->palavra, vetorPalavras [auxiliar->pai->indice].palavra);
		novoElemento->prox = inicio;
		inicio = novoElemento;
		auxiliar = auxiliar->pai;
	}
	//Printa a lista final
	listaString *auxiliarPercorreLista = inicio;
	if (verificaFrase == 1)
	{
		while (auxiliarPercorreLista != NULL)
		{
			printf("%s ", auxiliarPercorreLista->palavra);
			auxiliarPercorreLista = auxiliarPercorreLista->prox;
		}
	}
		printf("\n");

	return;
}

int EncontraMinimo (vertice *vetorPalavrasHeap, int numeroPalavrasDistintas) 
{
	int indice;
	int minimo = 4000000000;

	for (int i = 0; i< numeroPalavrasDistintas; i++)
	{
		if (minimo > vetorPalavrasHeap [i].distancia && vetorPalavrasHeap [i].verificador != -1) {
			minimo = vetorPalavrasHeap [i].distancia;
			indice = i;
		}
	}

	return indice;
}



