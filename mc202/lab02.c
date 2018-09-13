#include <stdio.h>
#include <stdlib.h>

typedef struct requisicoes {
	char tipo;
	int acesso;
} requisicoes;

typedef struct no {
	int num;
	struct no *prox;
} no;

typedef struct head {
	no *lista;
} head;

//Cria a lista a partir do vetor lido em main
void criar_lista (head *heads, int list [], int tam);
//Insere elemento na lista a partir das requisições 
no *inserir (head *heads, int entr, int count []);
//Remove elemento da lista a partir das requisições
void remover (head *heads, int entr, int count []);
//Move para a frente o elemento acessado
void MTF (head *heads, int entr, int count []);
//Troca de posição com o anterir o elemento acessado
void TR (head *heads, int entr, int count []);
//Troca de posição com o anterior o elemento insido
void TR2 (head *heads, no *auxantant, int count []);
//Libera a memoria alocada pelo programa
void libera_memoria (head *head);

int main (void) {
	int tam, req; //tamanho, numero de requisições
	int *list; //Vetor da lista, que sera passado para uma lista ligada
	requisicoes *requis; //Vetor das requisições
	int i; //Contador
	char c;
	head heads;
	int count [2]; //Contador para MTF e TR
	no *aux;

	//Inicilizando variaveis
	heads.lista = NULL;
	count [0] = 0; //MTF
	count [1] = 0; //TR

	//Lendo tamanho e numero de requisições
	scanf ("%d %d", &tam, &req);

	//Alocando vetor da lista
	list = (int *) malloc (tam * sizeof (int));
	//Alocando vetor das requisĩções
	requis = (requisicoes *) malloc (req * sizeof (requisicoes));

	for (i=0; i<tam; i++) {
		scanf ("%d", &list [i]);
	}

	//Caso seja nescessario colocar mais uma leitura para o \r
	scanf ("%c", &c); //Le o enter pós numero
	scanf ("%c", &c);


	for (i=0; i<req; i++) {
		scanf ("%c", &requis [i].tipo);
		scanf ("%c", &c); //Le o espaço
		scanf ("%d", &requis [i].acesso);
		//Caso seja nescessario colocar mais uma leitura para o \r
		scanf ("%c", &c); //Le o enter
		scanf ("%c", &c);
	}


	//Rodando para MTF
	criar_lista (&heads, list, tam);
	for (i=0; i<req; i++) {
		//Gerencia os casos acessar, inserir e remover
		switch (requis [i].tipo) {
			case 'a':
				MTF (&heads, requis [i].acesso, count);
				break;
			case 'i':
				inserir (&heads, requis [i].acesso, count);
				break;
			case 'r':
				remover (&heads, requis [i].acesso, count);
				break;
		}
	}

	aux = heads.lista;
	printf("%d\n", count [0]);
	while (aux != NULL) {
		printf("%d ", aux->num);
		aux = aux->prox;
	}
	printf("\n");
	libera_memoria (&heads);

	//Rodando para TR
	count [1] = 0; //TR
	criar_lista (&heads, list, tam);
	for (i=0; i<req; i++) {
		//Gerencia os casos acessar, inserir e remover
		switch (requis [i].tipo) {
			case 'a':
				TR (&heads, requis [i].acesso, count);
				break;
			case 'i':
				aux = inserir (&heads, requis [i].acesso, count);
				TR2 (&heads, aux, count);
				break;
			case 'r':
				remover (&heads, requis [i].acesso, count);
				break;
		}
	}
	
	aux = heads.lista;
	printf("%d\n", count [1]);
	while (aux != NULL) {
		printf("%d ", aux->num);
		aux = aux->prox;
	}
	printf("\n");
	libera_memoria (&heads);
	
	return 0;
}

void criar_lista (head *heads, int list [], int tam) {
	no *novo, *aux;
	int i;

	heads->lista = (no *) malloc (sizeof (no));
	heads->lista->num = list [tam-1];
	heads->lista->prox = NULL;

	for (i=tam-2; i>=0; i--) {
		novo = (no *) malloc (sizeof (no));
		novo->num = list [i];
		novo->prox = NULL;
		aux = heads->lista;
		heads->lista = novo;
		novo->prox = aux;
	}
	
	return;
}

no *inserir (head *heads, int entr, int count []) {
	no *novo, *aux, *auxant; //aux aponta para o elemento, auxant aponta para o elemento anterior

	aux = heads->lista;
	//Insere no inicio
	if (aux == NULL) {
		auxant = aux;
		novo = (no *) malloc (sizeof (no));
		novo->num = entr;
		novo->prox = NULL;
		heads->lista = novo;
		count [0]++;
		count [1]++;
		count [0]++;
		count [1]++;
		return heads->lista;
	}
	//Percorre a lista e insere no final
	else {
		auxant = aux;
		while (aux->prox != NULL) {
			auxant = aux;
			aux = aux->prox;
			count [0]++;
			count [1]++;
		}
	
		novo = (no *) malloc (sizeof (no));
		novo->num = entr;
		novo->prox = NULL;
		aux->prox = novo;
		count [0]++;
		count [1]++;
		count [0]++;
		count [1]++;
	}

	return auxant;
}

void remover (head *heads, int entr, int count []) {
	no *aux, *auxant;

	aux = heads->lista;

	//lista vazia não faz nada
	if (aux == NULL){
		count [0]++;
		count [1]++;
		return;
	}

	//Elemento a ser removido esta na cabeça
	if (aux->num == entr){
		heads->lista = aux->prox;
		free (aux);
		aux = NULL;
		count [0]++;
		count [1]++;
		return;
	}

	//Lista com elementos, procura o elemento e remove ele
	if (aux != NULL && aux->num != entr) {
		while (aux->prox->num != entr && aux != NULL) {
			aux = aux->prox;
			count [0]++;
			count [1]++;
		}

		if (aux == NULL){
			count [0]++;
			count [1]++;
			return;
		}

		auxant = aux;
		aux = aux->prox;

		auxant->prox = aux->prox;
		free (aux);
		aux = NULL;
		count [0]++;
		count [1]++;
		count [0]++;
		count [1]++;
		return;
	}

	return;	
}

void MTF (head *heads, int entr, int count []) {
	no *aux, *auxant;

	aux = heads->lista;
	count [0] ++;

	//Lista tem 1 elemento e não é alterada
	if (aux->prox == NULL){
		return;
	}	

	//Elemento ja esta no inicio
	if (aux->num == entr) {
		return;
	}

	if (aux->prox->num == entr) {
		auxant = aux;
		aux = aux->prox;

		auxant->prox = aux->prox;
		aux->prox = heads->lista;
		heads->lista = aux;
		count [0]++;
		return;
	}

	//Percorre a lista para encontrar o elemento e mover para a frente
	else {
		while (aux->prox->num != entr) {
			aux = aux->prox;
			count [0] ++;
			if (aux->prox == NULL){
				count [0] ++;
				return;
			}		
		}

		auxant = aux;
		aux = aux->prox;

		auxant->prox = aux->prox;
		aux->prox = heads->lista;
		heads->lista = aux;
		count [0] ++;
	}

	return;
}

void TR (head *heads, int entr, int count []) {
	no *aux, *auxant, *auxantant;

	count [1] ++; 
	aux = heads->lista;

	//Lista tem 1 elemento e não é alterada
	if (aux->prox == NULL){
		return;
	}

	//Elemento esta na cabeça
	if (aux->num == entr) {
		return;
	}

	//Elemento é o segundo da lista	
	if (aux->prox->num == entr) {
		auxant = aux;
		aux = aux->prox;

		auxant->prox = aux->prox;
		aux->prox = heads->lista;
		heads->lista = aux;
		count [1]++;
		return;
	}

	else {
		//Percorre a lista para encontrar o elemento
		while (aux->prox->prox->num != entr){
			aux = aux->prox;
			count [1] ++;
			if (aux->prox->prox == NULL) {
				count [1] ++;
				return;
			}
		}
		auxantant = aux;
		auxant = aux->prox;
		aux = auxant->prox;

		auxant->prox = aux->prox;
		auxantant->prox =aux;
		aux->prox = auxant;
		count [1]++;
		count [1]++;
		return;
	}

	return;
}

void TR2 (head *heads, no *auxantant, int count []) {
	no *aux, *auxant;

	//Um elemento na lista
	if (auxantant->prox == NULL) {
		return;
	}

	auxant = auxantant->prox;

	//Elemento é o segundo da lista
	if (auxant->prox == NULL) {
		auxantant->prox = auxant->prox;
		auxant->prox = heads->lista;
		heads->lista = auxant;
		return;
	}

	aux = auxant->prox;

	//Elemento genérico, que não cai nos casos anteriores
	auxant->prox = aux->prox;
	auxantant->prox = aux;
	aux->prox = auxant;

	return;
}

void libera_memoria (head *heads) {
	no *aux;

	aux = heads->lista;
	while (aux != NULL) {
		aux = aux->prox;
		free (heads->lista);
		heads->lista = aux;
	}

	return;
}