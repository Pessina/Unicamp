#include <stdio.h>
#include <stdlib.h>

typedef struct pilha {
	int num;
	int N;
	char cor;
	struct pilha *prox;
} pilha;

typedef struct head {
	pilha *lista;
} head;

typedef struct entrada {
	int val;
	char cor;
} entrada;

void empilhar (entrada atual, head *heads);
void desempilhar (entrada atual, head *heads, entrada saida [], int *contador);

int main (void) {
	int tam, i, j; //tam = tamanho da entrada
	char auxcor;
	int auxval;
	entrada auxentr;
	int contador; //Guarda o indice do vetor de saida
	entrada *entradas, *saida;
	head heads;
	int contpos, contneg; //Conta o numero de numero postivos e negativos na entrada

	//Inicializando variaveis;
	heads.lista = NULL;
	contador = 0;
	contpos = 0;
	contneg = 0;

	//Le o tamanho e aloca um vetor com o tamanho da entrada
	scanf ("%d", &tam);

	//Verifica se tam é par
	if (tam%2 != 0){
		printf("sequencia invalida ou nao pode colorir\n");
		return 0;
	}

	//Aloca vetor para entradas
	entradas = (entrada *) malloc (tam * sizeof (entrada));
	for (i=0; i<tam; i++) {
		scanf ("%d", &entradas [i].val);
	}

	//Verifica se há duas mokshakas iniciais
	for (i=0; i<tam; i++) {
		if (entradas [i].val > 0)
			contpos++;
		else
			contneg ++;
		if (contneg == contpos && i < tam-1) {
			printf("sequencia invalida ou nao pode colorir\n");
			return 0;
		}

	}

	//Cria um vetor para printar a saida
	saida = (entrada *) malloc (tam/2 * sizeof (entrada));

	//Percorre a entrada empilhando e desemppilhando
	for (i=0; i<tam; i++) {
		//Para valores negativos emppilha
		if (entradas [i].val < 0)
			empilhar (entradas [i], &heads);
		//Para valores positivos desempilha
		if (entradas [i].val > 0)
			desempilhar (entradas [i], &heads, saida, &contador);
		//Verifica se desempilhar retornou sequencia invalida		
		if (contador == -1)
			return 0;
	}

	//Organizando o vetor em ordem crescente
	for (i=0; i<tam/2; i++) {
		for (j=0; j<tam/2; j++) {
			if (saida [i].val > saida [j].val) {
				auxval = saida [i].val;
				auxcor = saida [i].cor;
				saida [i].val = saida [j].val;
				saida [i].cor = saida [j].cor;
				saida [j].val = auxval;
				saida [j].cor = auxcor;
			}

		}
	}

	auxentr.val = saida [0].val;
	auxentr.cor = saida [0].cor;

	//Verificando se a sequencia é valida
	for (i=0; i<tam/2; i++) {
		if (auxentr.val == saida [i].val){
			if (auxentr.cor != saida [i].cor){
				printf("sequencia invalida ou nao pode colorir\n");
				return 0;
			}
		}
		else {
			auxentr.val = saida [i].val;
			auxentr.cor = saida [i].cor;
		}
	}

	//Printando a saida
	printf("sequencia valida pode ser colorida\n");
	if (saida [0].cor == 'a')
		printf("%d: azul\n", (saida [0].val*-1));
	else
		printf("%d: vermelho\n", (saida [0].val*-1));
	for ( i=1; i<tam/2; i++) {
		if (saida [i].val != saida [i-1].val){
			if (saida [i].cor == 'a')
				printf("%d: azul\n", (saida [i].val*-1));
			else
				printf("%d: vermelho\n", (saida [i].val*-1));
		}
	}

	//Liberando a memoria alocada
	free (entradas);
	free (saida);

	return 0;
}

void empilhar (entrada atual, head *heads) {
	pilha *novo;

	//Define a cor de cada elemento de acordo com sua paridade
	if (atual.val%2 == 0)
		atual.cor = 'a';
	else
		atual.cor = 'r';

	//Insere na lista vazia
	if (heads->lista == NULL) {
		heads->lista = (pilha *) malloc (sizeof(pilha));
		heads->lista->num = atual.val;
		heads->lista->cor = atual.cor;
		heads->lista->N = 0;
		heads->lista->prox = NULL;
	}
	//Insere em lista não vazia
	else {
		novo = (pilha *) malloc (sizeof (pilha));
		novo->num = atual.val;
		novo->cor = atual.cor;
		novo->prox = heads->lista;
		novo->N = 0;
		heads->lista = novo;
	}

	return;
}


void desempilhar (entrada atual, head *heads, entrada saida [], int *contador){
	pilha *aux;

	//Verificando se o elemento a ser desempilhado é valido
	if ((heads->lista->num*-1) != atual.val){
		printf("sequencia invalida ou nao pode colorir\n");
		*contador = -1;
		return;
	}

	aux = heads->lista;
	if (heads->lista->prox != NULL)
		heads->lista = heads->lista->prox;

	//Define a cor do elemento a ser desempilhado
	if ((aux->N+(aux->num*-1))%2 == 0)
		aux->cor = 'a';
	else
		aux->cor = 'r';

	//Verifica a cor dos subordinados para aumentar o N
	if (aux->cor == 'a')
		heads->lista->N++;

	//Passando os dados para o vetor de saida
	saida [*contador].val = aux->num;
	saida [*contador].cor = aux->cor;
	*contador = *contador + 1;

	//Liberando memoria
	free (aux);

	return;
}


