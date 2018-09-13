#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char tam_nome [10];

//Ingredites do restaurante
typedef struct ingrediente {
	tam_nome nome;
	char quantidade_descongelada;
	char quantidade_10min;
	char quantidade_0min;
	int tempo_de_espera; 
	struct ingrediente *esq, *dir;
} ingrediente;

//Ingrediente do pedido de cada cliente
typedef struct ingrediente_pedido {
	ingrediente *point_ingrediente;
	struct ingrediente_pedido *prox;
} ingrediente_pedido;

//Fila de clientes
typedef struct fila {
	int senha;
	int tempo_chegada;
	ingrediente_pedido *pedido;
	struct fila *prox;
} fila;

//Insere o iingrediente na arvore de ingredientes 
ingrediente *insere_na_arvore (ingrediente **aux, tam_nome nome, int tempo_chegada, int *point_tempo);
//insere o cliente na fila 
void inserir_cliente (fila **inicio, int tempo_chegada, ingrediente **lista_ingredientes, int *point_tempo);
//Rotaciona os nós
void rotacionar_dir (ingrediente **raiz);
void rotacionar_esq (ingrediente **raiz);
//Atualiza os ingredientes quando uma pizza é feita
void atualiza_ingredientes_pizza (fila *cliente);
//Atuliza os ingredientes com o tempo, fazendo os descongelar
void atualiza_ingredientes_pospizza (ingrediente *aux);
//Verifica se o pedido do cliente é realizavel no momento
int verifica_pedido (fila *cliente);
//Percorre a fila verificando se o pedido de algum cliente é viavel
int verifica_fila (fila **inicio, ingrediente **lista_ingredientes, int *point_tempo);
//Remove o cliente da fila e libera a memoria
void remove_cliente (fila **aux);
void remove_cliente2 (fila *aux);
//Destroi a arvore
void free_arvore (ingrediente *aux);

void imprime_arvore (ingrediente *aux2);
void imprime_fila (fila *aux);

int main (void) {
	int tempo_chegada;
	fila *inicio = NULL;
	ingrediente *lista_ingredientes = NULL;
	//Armazena o tempo atual, da pizzaria
	int tempo;
	int *point_tempo = &tempo;
	int ver_return_fila = 1;

	//Le as entradas até o final do arquivo
	scanf ("%d", &tempo_chegada);
	tempo = tempo_chegada;
	while (!feof (stdin)) {
		inserir_cliente (&inicio, tempo_chegada, &lista_ingredientes, point_tempo);
		scanf ("%d", &tempo_chegada);

		//Testes
		//printf("\n\n\n\n");
		//imprime_arvore (lista_ingredientes);


		//Percorre a fila até que o tempo da pizzaria se iguale ao tempo da chegada do proximo cliente
		while (tempo < tempo_chegada){
			if (ver_return_fila == 0) {
				atualiza_ingredientes_pospizza (lista_ingredientes);
				tempo = tempo + 1;
			}
			ver_return_fila = 0;
			if (inicio != NULL)
				ver_return_fila = verifica_fila (&inicio, &lista_ingredientes, point_tempo);
		}
		//Percorre a fila antes de inserir um novo cliente
		do {
			if (inicio != NULL){
				ver_return_fila = verifica_fila (&inicio, &lista_ingredientes, point_tempo);
			}
			else
				break;
		} while (ver_return_fila != 0); 
		ver_return_fila = 1;
	}

	//Percorre a fila até ela acabar
	while (inicio  != NULL) {
		ver_return_fila = verifica_fila (&inicio, &lista_ingredientes, point_tempo);
		//imprime_arvore (lista_ingredientes);
		if (ver_return_fila == 0)
			atualiza_ingredientes_pospizza (lista_ingredientes);
	}

	free_arvore (lista_ingredientes);

	return 0;
}


void inserir_cliente (fila **inicio, int tempo_chegada, ingrediente **lista_ingredientes, int *point_tempo) {
	fila *aux = *inicio;
	fila *novo_cliente;
	ingrediente_pedido *novo;
	tam_nome nome;
	char c;
	static int i = 1;

	//Adiciona o cliente na fila vazia
	if (aux == NULL) {
		aux = (fila *) malloc (sizeof (fila));
		aux->tempo_chegada = tempo_chegada;
		aux->prox = NULL;
		aux->pedido = NULL;
		aux->senha = i++;
		//Insere o pedido do cliente
		do {
			novo = (ingrediente_pedido *) malloc (sizeof (ingrediente_pedido));
			scanf ("%s", nome);
			novo->point_ingrediente = insere_na_arvore (lista_ingredientes, nome, tempo_chegada, point_tempo);
			novo->prox = NULL;
			novo->prox = aux->pedido;
			aux->pedido = novo;
			c = getchar ();
			if (feof (stdin))
				return;
		} while (c != '\n' && c != '\r');
		if (verifica_pedido (aux) == 1){
			*point_tempo = *point_tempo + 1;
			atualiza_ingredientes_pizza (aux);
			atualiza_ingredientes_pospizza (*lista_ingredientes);
			remove_cliente (&aux);
			return;
		}
		(*inicio) = aux;
	}
	//Adiciona o cliente na fila
	else {
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		novo_cliente = (fila *) malloc (sizeof (fila));
		novo_cliente->tempo_chegada = tempo_chegada;
		novo_cliente->prox = NULL;
		novo_cliente->pedido = NULL;
		novo_cliente->senha = i++;
		//Insere o pedido do cliente
		do {
			novo = (ingrediente_pedido *) malloc (sizeof (ingrediente_pedido));
			scanf ("%s", nome);
			if (feof (stdin))
				return;
			novo->point_ingrediente = insere_na_arvore (lista_ingredientes, nome, tempo_chegada, point_tempo);
			novo->prox = NULL;
			novo->prox = novo_cliente->pedido;
			novo_cliente->pedido = novo;
			c = getchar ();
			if (feof (stdin))
				return;
		} while (c != '\n' && c != '\r');
		if (verifica_pedido (novo_cliente) == 1){
			*point_tempo = *point_tempo + 1;
			atualiza_ingredientes_pizza (novo_cliente);
			atualiza_ingredientes_pospizza (*lista_ingredientes);
			remove_cliente (&novo_cliente);
			return;
		}
		aux->prox = novo_cliente;
	}
 
	return;
}

//Percorre a arvore recursivamente até encontrar null e inserir o elemento, depois sobe a arvore rotacinanado
//o elemento até o topo
ingrediente *insere_na_arvore (ingrediente **aux, tam_nome nome, int tempo_chegada, int *point_tempo) {
	ingrediente *novo;

	if (*aux == NULL){
		if (tempo_chegada < 4 && *point_tempo < 4) {
			(*aux) = (ingrediente *) malloc (sizeof (ingrediente));
			strcpy ((*aux)->nome, nome);
			(*aux)->quantidade_descongelada = 2;
			(*aux)->quantidade_10min = 0;
			(*aux)->quantidade_0min = 0;
	    	(*aux)->tempo_de_espera = 0;
			(*aux)->esq = NULL;
			(*aux)->dir = NULL;
		}
		else {
			(*aux) = (ingrediente *) malloc (sizeof (ingrediente));
			strcpy ((*aux)->nome, nome);
			(*aux)->quantidade_descongelada = 0;
			(*aux)->quantidade_10min = 0;
			(*aux)->quantidade_0min = 2;
	    	(*aux)->tempo_de_espera = 0;
			(*aux)->esq = NULL;
			(*aux)->dir = NULL;
		}
		return *aux;
	}
	
	if (strcmp ((*aux)->nome, nome) == 0)
		return *aux;

	if (strcmp ((*aux)->nome, nome)<0) {
		novo = insere_na_arvore (&(*aux)->dir, nome, tempo_chegada, point_tempo);
		rotacionar_esq (aux);
	}
	else{
		novo = insere_na_arvore (&(*aux)->esq, nome, tempo_chegada, point_tempo);
		rotacionar_dir (aux);
	}

	return novo;
}

int verifica_fila (fila **inicio, ingrediente **lista_ingredientes, int *point_tempo) {
	fila *aux = *inicio;
	fila *auxant;
	int ver_return = 0;

	auxant = aux;
	while (aux != NULL) {
		if (verifica_pedido (aux) == 1) {
			if (ver_return != 1) {
				*point_tempo = *point_tempo + 1;
				atualiza_ingredientes_pizza (aux);
				atualiza_ingredientes_pospizza (*lista_ingredientes);
				if (auxant != aux){
					remove_cliente (&aux);
					*inicio = aux->prox;
				}
				else {
					*inicio = aux->prox;
					remove_cliente (&aux);
				} 
				ver_return = 1;
			}
		}
		auxant = aux;
		aux = aux->prox;
	}

	if (ver_return == 1) 
		return 1;
	else
		return 0;
}

int verifica_pedido (fila *cliente) {
	ingrediente_pedido *aux = cliente->pedido;
	int ver_return = 1;

	while (aux != NULL) {
		aux->point_ingrediente->tempo_de_espera = 0;
		if (aux->point_ingrediente->quantidade_descongelada == 0){
			if (aux->point_ingrediente->quantidade_0min + aux->point_ingrediente->quantidade_10min == 0)
				aux->point_ingrediente->quantidade_0min = 2;
			ver_return = 0; 
		}
		aux = aux->prox;
	}

	if (ver_return == 0)
		return 0;
	else		
		return 1;
}

void atualiza_ingredientes_pizza (fila *cliente) {
	ingrediente_pedido *aux = cliente->pedido;

	while (aux != NULL) {
		aux->point_ingrediente->quantidade_descongelada--;
		//Testando if
		if (aux->point_ingrediente->quantidade_descongelada + aux->point_ingrediente->quantidade_10min + aux->point_ingrediente->quantidade_0min < 2)
			aux->point_ingrediente->quantidade_0min++;
		aux->point_ingrediente->tempo_de_espera = 0;
		aux = aux->prox;
	}
	return;
}

void atualiza_ingredientes_pospizza (ingrediente *aux) {

	if (aux != NULL) {
		atualiza_ingredientes_pospizza ((aux->esq));
		(aux)->quantidade_descongelada += (aux)->quantidade_10min;
		(aux)->quantidade_10min = 0;
		(aux)->quantidade_10min = (aux)->quantidade_0min;
		(aux)->quantidade_0min = 0;
		(aux)->tempo_de_espera++;
		if ((aux)->tempo_de_espera > 5){
			(aux)->quantidade_descongelada = 0;
			(aux)->quantidade_10min = 0;
			(aux)->quantidade_0min = 0;
		}
		atualiza_ingredientes_pospizza ((aux->dir));
	}

	return;
}

void remove_cliente (fila **aux) {
	ingrediente_pedido *aux2 = (*aux)->pedido;
	ingrediente_pedido *auxant = aux2;

	printf("%d ", (*aux)->senha);
	while (aux2 != NULL) {
		auxant = aux2;
		aux2 = aux2->prox;
		free (auxant);
	}
	free (*aux);

	return;
}

void remove_cliente2 (fila *aux) {
	fila *aux_free = aux->prox;
	ingrediente_pedido *aux2 = aux->pedido;
	ingrediente_pedido *auxant = aux2;

	printf("%d ", (aux)->prox->senha);
	(aux)->prox = (aux)->prox->prox;
	while (aux2 != NULL) {
		auxant = aux2;
		aux2 = aux2->prox;
		free (auxant);
	}
	free (aux_free);
	return;
}

void free_arvore (ingrediente *aux) {

	if (aux == NULL)
		return;
	else {
		free_arvore (aux->dir);
		free_arvore (aux->esq);
	}

	free (aux);

	return;
}


void rotacionar_dir (ingrediente **raiz) {
	ingrediente *a, *b;

	b = *raiz;
	a = (*raiz)->esq;

	b->esq = a->dir;
	a->dir = b;
	*raiz = a;

	return;
}

void rotacionar_esq (ingrediente **raiz) {
	ingrediente *a, *b;

	b = *raiz;
	a = (*raiz)->dir;

	b->dir = a->esq;
	a->esq = b;
	*raiz = a;

	return;
}

void imprime_arvore (ingrediente *aux2) {

		if (aux2 != NULL) {
			imprime_arvore (aux2->esq);
			printf("Nome: %s\n", aux2->nome);
			printf("Quantidades: %d %d %d\n", aux2->quantidade_descongelada, aux2->quantidade_10min, aux2->quantidade_0min);
			printf("Tempo de Espera: %d\n", aux2->tempo_de_espera);
			imprime_arvore (aux2->dir);
		}
}

void imprime_fila (fila *aux) {
	ingrediente_pedido *aux2;

	printf("Saida\n");
	while (aux != NULL) {
		printf("Senha: %d Tempo Chegada: %d\n", aux->senha, aux->tempo_chegada);
		aux2 = aux->pedido;
		printf("Pedido:\n");
		while (aux2 != NULL) {
			printf(" -%s\n", aux2->point_ingrediente->nome);
			aux2 = aux2->prox;
		}
		aux = aux->prox;
	}

	return;
}

