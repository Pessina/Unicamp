#include <stdio.h>
#include <stdlib.h>

typedef struct  no {
	int num;
	struct no *prox;
}no;

typedef struct head  {
	int m, n, p; //count = contador do numero de elementos da lista
	int m1, n1, p1; //Verificadores de m, n e p
	no *lista;
	//Apontadores para m, n e p da lista. Para serem reutilizados nas funções seguintes na ordem 1, 2 e 3
	no *mpos, *npos, *ppos;
}head;


void inserir (head *heads); //Cria a lista
no* inverte_lista (head *heads); //Inverte a lista criada por inserir
void func1 (head *heads); //Imprime de m a n
void func2 (head *heads); //Imprime de n a p
void func3 (head *heads); //Imprime de p ao ultimo
void liberar (head *heads); //Libera a memoria

int main(int argc, char const *argv[]) {
	head heads;
	no *aux;

	//Leitura e inversão da lista
	inserir (&heads);
	aux = inverte_lista (&heads);

	//Leitura dos paramentros m, n e p
	scanf ("%d %d %d", &heads.m ,&heads.n ,&heads.p);

	//Saidas
	//Printando a lista original de entrada
	printf("original");
	while (aux != NULL) {
		printf(" %d", aux->num);
		aux = aux->prox;
	}
	printf ("\n");

	//Printando paramentros m, n e p
	printf("m=%d, n=%d, p=%d\n", heads.m ,heads.n ,heads.p);
 
 	//Chamada das tres funções para imprimir as saidas
	printf("primeira");
	func1 (&heads);
	printf("\n");
	printf("segunda");
	func2 (&heads);
	printf("\n");
	printf("terceira");
	func3 (&heads);

	printf ("\n");

	//Liberando a memoria
	liberar (&heads);

	return 0;
}

//Montando a lista
void inserir (head *heads) {
	char c; //Variável de teste para fim de linha
	no *aux;

	//Criação da cabeça da lista
	heads->lista = (no *) malloc (sizeof (no));
	scanf ("%d", &heads->lista->num);
	scanf ("%c", &c);
	heads->lista->prox = NULL;

	//Ao fim da linha é parada a leitura da lista
	while (c != '\n' && c != '\r') {
		aux = (no *) malloc (sizeof (no));
		scanf ("%d", &aux->num);
		scanf ("%c", &c);
		aux->prox = heads->lista;
		heads->lista = aux;
	}

	return;
}

//Invertendo a lista
no* inverte_lista (head *heads) {
	no *auxant, *aux, *auxprox;

	//Iniciando os 3 apontadores que correrão a lista
	auxant = heads->lista;
	aux = auxant->prox;
	auxprox = aux->prox;

	//Percorrendo a lista e invertendo os apontadores
	while (auxprox != NULL) {
		aux->prox = auxant;
		auxant = aux;
		aux = auxprox;
		auxprox = auxprox->prox;
	}

	aux->prox = auxant;
	auxant = aux;

	heads->lista->prox = NULL;
	heads->lista = aux; //Resetando a cabeça

	return heads->lista;
}

void func1 (head *heads) {
	no *aux, *auxset, *auxset2;
	//aux percorre a lista, auxset determina o inicio do print, auxset2 determina o fim do print

	//Inicializando os valores das variaveis verificadoras. 1 existe, 0 não existe
	heads->m1 = heads->n1 = heads->p1 = 0;

	//Percorrendo para verificar existencia de m
	aux = heads->lista;
	while (aux != NULL) {
		if (aux->num == heads->m){ //Encontra m, e seta a posição dele
			heads->m1 = 1;
			auxset = aux;
		}
		aux = aux->prox;
	}
	if (heads->m1 == 0) { //Não encontra m, e seta m = inicio
		heads->m = heads->lista->num;
		auxset = heads->lista;
	}

	//Setando a posição de m
	heads->mpos = auxset;

	//Seta aux para percorrer a partir de m
	aux = auxset;
	aux = aux->prox;
	while (aux != NULL) {
		if (aux->num == heads->n){ //Encontra m e printa de m a n
			heads->n1 = 1;
			auxset2 = aux;
			heads->npos = auxset2;
			if (auxset != auxset2) { //Verificando se não estão na mesma posição
				while (auxset != auxset2){
					printf (" %d", auxset->num);
					auxset = auxset->prox;
				}
				printf(" %d", auxset2->num);
				break;
			}
		}
		aux = aux->prox;
	}
	if (heads->n1 == 0){ //Não encontra n, e seta n=p se encontra p 
		aux = auxset;
		aux = aux->prox;
		while (aux != NULL) {
			if (aux->num == heads->p) {//printa de m a p
				heads->p1 = 1;
				auxset2 = aux;
				heads->npos = auxset2;
				if (auxset != auxset2) {
					while (auxset != auxset2){
						printf (" %d", auxset->num);
						auxset = auxset->prox;
					}
					printf(" %d", auxset2->num);
					break;
				}
			}
			aux = aux->prox;
		}
		if (heads->p1 == 0){//Não encontra p e faz p = ultimo e printa de m ao ultimo
			if (auxset->prox != NULL) {
				while (auxset != NULL) {
					printf(" %d", auxset->num);
					auxset = auxset->prox;
				}
			}
		} 
	}

	return;
} 

void func2 (head *heads) {
	no *aux, *auxset, *auxset2; 

	//Se n não existir ele é igual a pos de m
	if (heads->n1 == 0)
		auxset = heads->mpos;
	//se n existir ele é igual a posição de n ja encontrada na func1
	else
		auxset  = heads->npos;

	//Setando a posição de n, após a relização da condicionais a cima
	heads->npos = auxset;

	//Seta aux para percorrer a lista a partir de n
	aux = auxset;
	aux = aux->prox;
	while (aux != NULL){
		if (aux->num == heads->p){
			heads->p1 = 1;
			auxset2 = aux;
			heads->ppos = auxset2;
			if (auxset != auxset2) {
				while (auxset != auxset2){
					printf(" %d", auxset->num);
					auxset = auxset->prox;
				}
				printf(" %d", auxset->num);
				break;
			}
		}
		aux = aux->prox;
	}
		if (heads->p1 == 0){
			if (auxset->prox != NULL) {
				while (auxset != NULL) {
					printf(" %d", auxset->num);
						auxset = auxset->prox;
				}
			}
		}	

	return;
}

void func3 (head *heads) {
	no *auxset; 

	//Se p não existir ele é igual a npos
	if (heads->p1 == 0)
		auxset = heads->npos;
	//Se p existir ele é igual a ppos
	else
		auxset = heads->ppos;

	//Printa de p até o final da lista
	if (auxset->prox != NULL) {
		while (auxset != NULL) {
			printf(" %d", auxset->num);
			auxset = auxset->prox;
		}
	}

	return;	
}

void liberar (head *heads) {
	no* aux;

	aux = heads->lista;
	while (aux != NULL) {
		aux = heads->lista->prox;
		free (heads->lista);
		heads->lista = aux;
	}

	return;
}
