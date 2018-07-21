#include <stdio.h>
#include <stdlib.h>

//Vetor de prioridade do cache com base no tempo para a proxima chamada do numero
typedef struct heap
{
	int numero;
	int tempo_proxima_chamada;
}heap;

//Insere o elemento no Cache
void inserir (heap vetor_heap [], int numero, int j, int *point_tamanho);
//Caso o elemento ja esteja no cache, ele atualiza o novo tempo da proxima chamada, e atualiza o heap
void atualiza (heap vetor_heap [], int numero, int j, int i, int *point_tamanho);
//Remove o primeiro elemento do cache
void remover (heap vetor_heap [], int *point_tamanho);
//Verifica se o elemento chamado ja esta ou não no cache
int veririfca_heap (heap vetor_heap [], int tamanho_heap, int numero);

int main (void) {
	int tamanho_cache, numero_elementos_sistema, numero_acessos;
	int *vetor_acessos;
	heap *vetor_heap;
	int tamanho_heap = 0;
	int *point_tamanho = &tamanho_heap;
	int ver_heap;
	int i = 0;
	int j = 0;
	int contador_cache = 0;

	//Le a entrada e cria os vetores do cache e os acessos
	scanf ("%d %d %d", &tamanho_cache, &numero_elementos_sistema, &numero_acessos);
	vetor_acessos = (int *) malloc (numero_acessos * sizeof (int));
	vetor_heap = (heap *) malloc (tamanho_cache * sizeof (heap));

	//Lendo a entrada e associando a arvore
	for (i=0; i<numero_acessos; i++) {
		scanf ("%d", &vetor_acessos [i]);
	}

	//Percorre o vetor de acessos, e gerencia o cache, de acordo com as chamadas
	for (i=0; i<numero_acessos; i++) {
		ver_heap = veririfca_heap (vetor_heap, tamanho_heap, vetor_acessos [i]);
		if (ver_heap == -1) {
			for (j = i + 1; j<numero_acessos; j++) {
				if (vetor_acessos [i] == vetor_acessos [j])
					break;
				if (j == numero_acessos)
					j = numero_acessos+i;
			} 
			//i tempo atual, j tempo da proxima chamada
			if (tamanho_heap == tamanho_cache)
				remover (vetor_heap, point_tamanho);
			inserir (vetor_heap, vetor_acessos [i], j, point_tamanho);
			contador_cache++;
		}
		else {
			for (j = i + 1; j<numero_acessos; j++) {
				if (vetor_acessos [i] == vetor_acessos [j])
					break;
				if (j == numero_acessos)
					j = numero_acessos;
			} 
			atualiza (vetor_heap, vetor_acessos [i], j, ver_heap, point_tamanho);
		}
	}

	printf("%d\n", contador_cache);

	return 0;
}

void inserir (heap vetor_heap [], int numero, int j, int *point_tamanho) {
	int posicao;

	//Insere elemento
	vetor_heap [*point_tamanho].numero = numero;
	vetor_heap [*point_tamanho].tempo_proxima_chamada = j;
	posicao = *point_tamanho;
	*point_tamanho = *point_tamanho + 1;

	//Percorre o vetor de prioridade trocando os elementos
	while (posicao != 0) {
		if (vetor_heap [(posicao-2)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada || vetor_heap [(posicao-1)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada) {
			if (posicao%2 == 0){
				if (vetor_heap [(posicao-2)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada) {
					vetor_heap [posicao].numero = vetor_heap [(posicao-2)/2].numero;
					vetor_heap [posicao].tempo_proxima_chamada = vetor_heap [(posicao-2)/2].tempo_proxima_chamada;
					vetor_heap [(posicao-2)/2].numero = numero;
					vetor_heap [(posicao-2)/2].tempo_proxima_chamada = j;
				}
				posicao = (posicao-2)/2;
			}
			else{
				if (vetor_heap [(posicao-1)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada) {
					vetor_heap [posicao].numero = vetor_heap [(posicao-1)/2].numero;
					vetor_heap [posicao].tempo_proxima_chamada = vetor_heap [(posicao-1)/2].tempo_proxima_chamada;
					vetor_heap [(posicao-1)/2].numero = numero;
					vetor_heap [(posicao-1)/2].tempo_proxima_chamada = j;
				}
				posicao = (posicao-1)/2;
			}
		}
		else
			break;
	}

	return;
}

void remover (heap vetor_heap [], int *point_tamanho) {
	int posicao;

	*point_tamanho = *point_tamanho - 1;
	vetor_heap [0].numero = vetor_heap [*point_tamanho].numero;
	vetor_heap [0].tempo_proxima_chamada = vetor_heap [*point_tamanho].tempo_proxima_chamada;
	posicao = 0;

	//Percorre o vetor trocando os elementos
	while (posicao < *point_tamanho) {
		if (vetor_heap [posicao].tempo_proxima_chamada < vetor_heap [2*posicao+1].tempo_proxima_chamada || vetor_heap [posicao].tempo_proxima_chamada < vetor_heap [2*posicao+2].tempo_proxima_chamada) {
			if (vetor_heap [2*posicao+1].tempo_proxima_chamada < vetor_heap [2*posicao+2].tempo_proxima_chamada) {
				vetor_heap [posicao].tempo_proxima_chamada = vetor_heap [2*posicao+2].tempo_proxima_chamada;
				vetor_heap [posicao].numero = vetor_heap [2*posicao+2].numero;
				vetor_heap [2*posicao+2].tempo_proxima_chamada = vetor_heap [*point_tamanho].tempo_proxima_chamada;
				vetor_heap [2*posicao+2].numero = vetor_heap [*point_tamanho].numero;
				posicao = 2*posicao+2;
			}
			else {
				vetor_heap [posicao].tempo_proxima_chamada = vetor_heap [2*posicao+1].tempo_proxima_chamada;
				vetor_heap [posicao].numero = vetor_heap [2*posicao+1].numero;
				vetor_heap [2*posicao+1].tempo_proxima_chamada = vetor_heap [*point_tamanho].tempo_proxima_chamada;
				vetor_heap [2*posicao+1].numero = vetor_heap [*point_tamanho].numero;
				posicao = 2*posicao+1;
			}
		}
		else {
			break;
		}
	}


	return;
}

void atualiza (heap vetor_heap [], int numero, int j, int i, int *point_tamanho) {
	int posicao;

	vetor_heap [i].tempo_proxima_chamada = j;
	posicao = i;

	//Percorre o vetor de prioridade trocando os elementos
	while (posicao != 0) {
		if (vetor_heap [(posicao-2)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada || vetor_heap [(posicao-1)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada) {
			if (posicao%2 == 0){
				if (vetor_heap [(posicao-2)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada) {
					vetor_heap [posicao].numero = vetor_heap [(posicao-2)/2].numero;
					vetor_heap [posicao].tempo_proxima_chamada = vetor_heap [(posicao-2)/2].tempo_proxima_chamada;
					vetor_heap [(posicao-2)/2].numero = numero;
					vetor_heap [(posicao-2)/2].tempo_proxima_chamada = j;
				}
				posicao = (posicao-2)/2;
			}
			else{
				if (vetor_heap [(posicao-1)/2].tempo_proxima_chamada < vetor_heap [posicao].tempo_proxima_chamada) {
					vetor_heap [posicao].numero = vetor_heap [(posicao-1)/2].numero;
					vetor_heap [posicao].tempo_proxima_chamada = vetor_heap [(posicao-1)/2].tempo_proxima_chamada;
					vetor_heap [(posicao-1)/2].numero = numero;
					vetor_heap [(posicao-1)/2].tempo_proxima_chamada = j;
				}
				posicao = (posicao-1)/2;
			}
		}
		else
			break;
	}

	return;
}

int veririfca_heap (heap vetor_heap [], int tamanho_heap, int numero) {
	int i, ver_return = -1;

	for (i=0; i<tamanho_heap; i++) {
		if (vetor_heap [i].numero == numero){
			ver_return = i;
			break;
		}
	}

	return ver_return;
}

