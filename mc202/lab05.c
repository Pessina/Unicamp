//Solucionar os casos em que o nó de remover e buscar não existe
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char tam_entrada [6];
typedef char tam_nome [21];
typedef struct  no {
	tam_nome arquivo; //Nome do arquivo
	int fator_balanceamento_dir;
	int fator_balanceamento_esq;
	int fator_balanceamento;
	struct  no *esq, *dir;
} no;

void imprime_arvore_inorder (no **arvore);
//Bloco para inserir
void touch (no **aux, tam_nome inserir);
void inserir_inicio (no **aux, tam_nome inserir);
int inserir_meio (no **aux, tam_nome inserir);
//Bloco para remover
void rm (no **aux, tam_nome remover);
void remover_meio (no **aux, tam_nome remover);
int remove_prefix (no **aux, tam_nome remover);
int remove_palavra (no **aux, tam_nome remover);
int remove_no (no **aux);
void trocar (no ** aux2, no **aux);
//Bloco para buscar
void ls (no **arvore, tam_nome buscar);
void procurar (no **arvore, tam_nome buscar);
int procura_prefix (no **arvore, tam_nome buscar);
int procura_palavra (no **arvore, tam_nome buscar);
int imprime_no (no **aux);
//Rotacionar
void rotacionar_esq (no **aux);
void rotacionar_dir (no **aux);

void print_naotem (void);

int main (void) {
	tam_entrada entrada;
	tam_nome arquivo;
	no *arvore=NULL;

	while (scanf (" %s", entrada) != EOF && scanf (" %s", arquivo) != EOF) {
		switch (entrada [0]) {
			case 't':
				touch (&arvore, arquivo);
				break;
			case 'l':
				ls (&arvore, arquivo);
				break;
			case 'r':
				rm (&arvore, arquivo);
				break;
			default:
				//goto fim;
				break;
		}
	}
	//fim;

	//imprime_arvore_inorder (&arvore);

	return 0;
}

void touch (no **aux, tam_nome inserir) {

	if (*aux == NULL) 
		inserir_inicio (aux, inserir);
	else
		inserir_meio (aux, inserir);

	return;
}

void inserir_inicio (no **aux, tam_nome inserir) {

	*aux = (no *) malloc (sizeof (no));
	strcpy((*aux)->arquivo, inserir);
	(*aux)->fator_balanceamento_dir = 0;
	(*aux)->fator_balanceamento_esq = 0;
	(*aux)->fator_balanceamento = 0;
	(*aux)->dir = NULL;
	(*aux)->esq = NULL;

	return;
}

int inserir_meio (no **aux, tam_nome inserir) {
	int ver_return;

	if (*aux == NULL){
		*aux = (no *) malloc (sizeof (no));
		strcpy ((*aux)->arquivo, inserir);
		(*aux)->dir = NULL;
		(*aux)->esq = NULL;
		return 1;
	} 
	else {
		if (strcmp ((*aux)->arquivo, inserir)<0) {
			ver_return = inserir_meio (&((*aux)->dir), inserir);
			if (ver_return == 1) {
				if ((*aux)->dir == NULL) {
					(*aux)->fator_balanceamento_esq++;
				}
				if ((*aux)->esq == NULL) {
					(*aux)->fator_balanceamento_dir++;
				}
				else {
					return 0;
				}
			}
			if (ver_return == 2) {
				(*aux)->fator_balanceamento_dir++;
			}
			if (ver_return == 0){
				return 0;
			}
			(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
			if ((*aux)->fator_balanceamento == 2) {
				rotacionar_esq (aux);
				return 0;
			}
			if ((*aux)->fator_balanceamento == -2) {
				rotacionar_dir (aux);
				return 0;
			}
			return 2;
		}
		else{
			ver_return = inserir_meio (&((*aux)->esq), inserir);
			if (ver_return == 1) {
				if ((*aux)->dir == NULL) {
					(*aux)->fator_balanceamento_esq++;
				}
				if ((*aux)->esq == NULL) {
					(*aux)->fator_balanceamento_dir++;
				}
				else {
					return 0;
				}
			}
			if (ver_return == 2) {
				(*aux)->fator_balanceamento_esq++;
			}
			if (ver_return == 0) {
				return 0;
			}
			(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
			if ((*aux)->fator_balanceamento == 2) {
				rotacionar_esq (aux);
				return 0;
			}
			if ((*aux)->fator_balanceamento == -2) {
				rotacionar_dir (aux);
				return 0;
			}
			return 2;
		}
	}
}


void rm (no **aux, tam_nome remover) {

	if (*aux == NULL)
		print_naotem ();
	else 
		remover_meio (aux, remover);

	return;
}

void remover_meio (no **aux, tam_nome remover) {
	int ver_remover = 0;

	if (remover [strlen (remover)-1] == '*'){
		ver_remover = remove_prefix (aux, remover);
	}
	else{
		ver_remover = remove_palavra (aux, remover);
	}

	if (ver_remover == 0) {
		print_naotem ();
	}

	return;
}

int remove_prefix (no **aux, tam_nome remover) {
	int ver_remover_dir = 0, ver_remover_esq = 0, teste = 0;

		if (*aux == NULL){
			return 0;
		}

		ver_remover_dir = remove_prefix (&((*aux)->dir), remover);
		if (ver_remover_dir == 2) {
				(*aux)->fator_balanceamento_dir--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
				else {
					return 2;
				}
			}
			else if (ver_remover_dir == 1) {
				return 1;
			}
			else if (ver_remover_dir == 3) {
				(*aux)->fator_balanceamento_dir--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
				else {
					return 2;
				}
			}

		ver_remover_esq = remove_prefix (&((*aux)->esq), remover);
		if (ver_remover_esq == 2) {
				(*aux)->fator_balanceamento_esq--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
				else {
					return 2;
				}
			}
			else if (ver_remover_esq == 1) {
				return 1;
			}
			else if (ver_remover_esq == 3) {
				(*aux)->fator_balanceamento_esq--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
			}

		if (strncmp (remover, (*aux)->arquivo, strlen(remover)-1) == 0){
			if ((*aux)->dir == NULL || (*aux)->esq == NULL) {
				teste = 3;
			}
			remove_no (aux);
			if (teste == 3) {
				return 3;
			}
			return 1;
		}


		return 0;

}

int remove_palavra (no **aux, tam_nome remover) {
	int ver_remover_dir = 0, ver_remover_esq = 0, teste;

		if (*aux == NULL){
			return 0;
		}


		if (strcmp ((*aux)->arquivo, remover)<0){
			ver_remover_dir = remove_palavra (&((*aux)->dir), remover);
			if (ver_remover_dir == 2) {
				(*aux)->fator_balanceamento_dir--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
				else {
					return 2;
				}
			}
			else if (ver_remover_dir == 1) {
				return 1;
			}
			else if (ver_remover_dir == 3) {
				(*aux)->fator_balanceamento_dir--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
				else {
					return 2;
				}
			}
		}

		if (strcmp ((*aux)->arquivo, remover)>=0) {
			ver_remover_esq = remove_palavra (&((*aux)->esq), remover);
			if (ver_remover_esq == 2) {
				(*aux)->fator_balanceamento_esq--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
				else {
					return 2;
				}
			}
			else if (ver_remover_esq == 1) {
				return 1;
			}
			else if (ver_remover_esq == 3) {
				(*aux)->fator_balanceamento_esq--;
				(*aux)->fator_balanceamento = (*aux)->fator_balanceamento_dir - (*aux)->fator_balanceamento_esq;
				if ((*aux)->fator_balanceamento == 2) {
					rotacionar_esq (aux);
					return 1;
				}
				if ((*aux)->fator_balanceamento == -2) {
					rotacionar_dir (aux);
					return 1;
				}
			}
		}

		if (strncmp (remover, (*aux)->arquivo, strlen(remover)-1) == 0){
			if ((*aux)->dir == NULL || (*aux)->esq == NULL) {
				teste = 3;
			}
			remove_no (aux);
			if (teste == 3) {
				return 3;
			}
			return 1;
		}

		if (ver_remover_esq == 0 && ver_remover_dir == 0)
			return 0;

		return 4;

}


int remove_no (no **aux) {
	no *aux2 = *aux;

	if ((*aux)->dir != NULL && (*aux)->esq != NULL) {
		(aux2) = (aux2)->esq;
		if ((aux2)->dir == NULL) {
			(aux2)->dir = (*aux)->dir;
			(*aux) = (aux2);
		}
		else if ((aux2)->dir != NULL) {
			trocar (&((aux2)->dir), aux);
		} 

	}
	else if ((*aux)->dir == NULL && (*aux)->esq != NULL) {
		(*aux) = (*aux)->esq;
		//(*aux) = (*aux)->esq;
		//free (*aux2);	
	}
		
	else if ((*aux)->dir != NULL && (*aux)->esq == NULL){
		(*aux) = (*aux)->dir; 
		//(*aux) = (*aux)->dir;
		//free(*aux);
	}
	else if ((*aux)->dir == NULL && (*aux)->esq == NULL){
		*aux = NULL;
		//free (*aux2);
	}

	return 1;
}

void trocar (no ** aux2, no **aux) {
	no *aux3;

	if ((*aux2)->dir == NULL) {
		(*aux2)->dir = (*aux)->dir;
		(*aux) = (*aux2);
		return;
	}
	if ((*aux2)->dir->dir != NULL) {
		trocar (&((*aux2)->dir), aux);
	}
	else {
		aux3 = (*aux2)->dir;
		(*aux2)->dir = (*aux2)->dir->esq;
		aux3->dir = (*aux)->dir;
		aux3->esq = (*aux)->esq;
		(*aux) = aux3;
		//free (*aux);
		return;
	}

	return;
}

void ls (no **aux, tam_nome buscar) {

	if (*aux == NULL)
		print_naotem ();
	else 
		procurar (aux, buscar);

	return;
}

void procurar (no **aux, tam_nome buscar) {
	int ver_busca = 0;

	if (buscar [strlen (buscar)-1] == '*')
		ver_busca = procura_prefix (aux, buscar);
	else
		ver_busca = procura_palavra (aux, buscar);

	if (ver_busca == 0) {
		print_naotem ();
	}

	return;
}

int procura_prefix (no **aux, tam_nome buscar) {
	int ver_busca, ver_busca_dir = 0, ver_busca_esq = 0;

		if (*aux == NULL){
			return 0;
		}
	
		ver_busca_dir = procura_prefix (&((*aux)->dir), buscar);
		ver_busca_esq = procura_prefix (&((*aux)->esq), buscar);

		if (strncmp (buscar, (*aux)->arquivo, strlen(buscar)-1) == 0){
			ver_busca = imprime_no (aux);
		}

		if (ver_busca == 1) {
			return 1;
		}
		if (ver_busca_dir == 0 && ver_busca_esq == 0) {
			return 0;
		}

		return 4;
}

int procura_palavra (no **aux, tam_nome buscar) {
	int ver_busca = 0;

		if (*aux == NULL){
			return 0;
		}

		if (strcmp ((*aux)->arquivo, buscar)<0){
			ver_busca = procura_palavra (&((*aux)->dir), buscar);
		}
		if (strcmp ((*aux)->arquivo, buscar)>=0) {
			ver_busca = procura_palavra (&((*aux)->esq), buscar);
		}

		if (strcmp (buscar, (*aux)->arquivo) == 0){
			ver_busca = imprime_no (aux);
		}

		if (ver_busca == 1) {
			return 1;
		}
		else {
			return 0;
		}
}

int imprime_no (no **aux) {
	printf("%s\n", (*aux)->arquivo);
	return 1;
}

void imprime_arvore_inorder (no **aux) {

	if (*aux != NULL) {
		imprime_arvore_inorder(&(*aux)->esq);
		printf("%s %d\n", (*aux)->arquivo, (*aux)->fator_balanceamento);
		imprime_arvore_inorder(&(*aux)->dir);
	}

	return;
}


void rotacionar_esq (no **aux) {
	no *a, *b;

	b = *aux;
	a = b->dir;

	*aux = a;
	b->dir = a->esq;
	a->esq = b;
	a->fator_balanceamento = 0;
	a->fator_balanceamento_esq = 0;
	a->fator_balanceamento_dir = 0;
	b->fator_balanceamento = 0;
	b->fator_balanceamento_esq = 0;
	b->fator_balanceamento_dir = 0;


	return;
}

void rotacionar_dir (no **aux) {
	no *a, *b;

	b = *aux;
	a = b->esq;

	*aux = a;
	b->esq = a->dir;
	a->dir = b;
	a->fator_balanceamento = 0;
	a->fator_balanceamento_esq = 0;
	a->fator_balanceamento_dir = 0;
	b->fator_balanceamento = 0;
	b->fator_balanceamento_esq = 0;
	b->fator_balanceamento_dir = 0;

	return;
}



void print_naotem (void) {
	printf("nao existem arquivos com essa expressao\n");
	return;
 }
