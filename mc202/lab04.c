#include <stdio.h>
#include <stdlib.h>

#define max 26

//Armazena dados sobre as rainhas anteriores
typedef struct ver_ver{
	int lin;
	int col;
} ver_ver;

//Funções para letras
//Seleciona um elemento da linha 1
int set_linha1_letra (char **matrix, ver_ver *vetor_ver, int tam, char ver_num [], char ver_colunas []);
//Verifica os elementos da proxima linha utilizando do backtracking 
int ver_pos_letra (char **matrix, ver_ver *vetor_ver, int i, int tam, char ver_num [], char ver_colunas []);
//Verifica cada um dos tres casos da posição da rainha. Diagonal, coluna, posição
int verifica_casos_letra (ver_ver *vetor_ver,int i, int j, char p, int tam, char ver_num [], char ver_colunas []);

//Funções para numeros
//Seleciona um elemento da linha 1
int set_linha1_numero (char **matrix, ver_ver *vetor_ver, int tam, char ver_num [], char ver_colunas []);
//Verifica os elementos da proxima linha utilizando do backtracking 
int ver_pos_numero (char **matrix, ver_ver *vetor_ver, int i, int tam, char ver_num [], char ver_colunas []);
//Verifica cada um dos tres casos da posição da rainha. Diagonal, coluna, posição
int verifica_casos_numero (ver_ver *vetor_ver,int i, int j, char p, int tam, char ver_num [], char ver_colunas []);

//Printa as saidas
void print_tem (void);
void print_nao (void);
//Libera a memroria
void free_mem (char **matrix, int tam);

int main (void) {
	int tam, ver; //Tamanho da matrix, e variavel de verificação
	char **matrix; //Apontador para matrix, tabuleiro
	int i;
	ver_ver *vetor_ver;
	char ver_colunas [max]; //Armazena e indexa, as colunas das damas
	char ver_num [max]; //Armazena e indexa as posições das damas

	scanf ("%d", &tam);
	//Impossivel dispor damas de forma  que não se ataquem
	if (tam == 0 || tam == 2 || tam == 3) {
		print_nao ();
		return 0;
	}
	//Disposição unica, não ha damas para atacar ela
	if (tam == 1) {
		print_tem ();
		return 0;
	}

	//Criação e leitura do tabuleiro
	matrix = (char **) malloc (tam * sizeof (char *));
	for (i=0; i<tam; i++) {
		matrix [i] = (char *) malloc ((tam+1) * sizeof (char));
	}
	vetor_ver = (ver_ver *) malloc (tam * sizeof (ver_ver));

	for (i=0; i<tam; i++) {
			scanf (" %[^\r]s", matrix [i]);
	}

	//Inicializando vetor de pos de rainhas
	for (i=0; i<tam; i++) {
		vetor_ver [i].lin = 0;
		vetor_ver [i].col = 0;
	}

	//Incializando vetores de indexamento
	for (i=0; i<max; i++) {
		ver_num [i] = 0;
		ver_colunas [i] = 0;
	}

	//Chamada para letras
	if (tam > 9) {	
		//Chamada para selecionar um elemento da primeira linha
		ver = set_linha1_letra (matrix, vetor_ver, tam, ver_num, ver_colunas);
	}
	//Chamada pra numeros
	else {
		//Chamada para selecionar um elemento da primeira linha
		ver = set_linha1_numero (matrix, vetor_ver, tam, ver_num, ver_colunas);
	}
	
	//Printa as saidas
	if (ver == 1)
		print_tem ();
	else
		print_nao ();

	//Libera a memoria
	free_mem (matrix, tam);
	free (matrix);
	free(vetor_ver);
	return 0;
}

int set_linha1_letra (char **matrix, ver_ver *vetor_ver, int tam, char ver_num [], char ver_colunas []) {
	int j, i, ver;

	//Seleciona a primeira linha
	i = 0;

	//Seleciona um elemento da primeira linha, e chama ver_pos para verificar
	//os elementos da segunda linha, qual deles pode ser utilizado para continar
	//testando, ou seja qual deles tem posição valida
	for (j=0; j<tam; j++) {
		//Monta o vetor com as posições das damas
		vetor_ver [i].lin = i;
		vetor_ver [i].col = j;
		ver_num [(int) matrix [i] [j]-65] = 1;
		ver_colunas [j] = 1;
		//Chama a verificação da segunda linha
		ver = ver_pos_letra (matrix, vetor_ver, i, tam, ver_num, ver_colunas);
		ver_num [(int) matrix [i] [j]-65] = 0;
		ver_colunas [j] = 0;
		if (ver == 1)
			return 1;
	}
	return 0;
}

int ver_pos_letra (char **matrix, ver_ver *vetor_ver, int i, int tam, char ver_num [], char ver_colunas []) {
	int vernum, ver;
	int j;

	//Desce de linha
	i++;

	for (j=0; j<tam; j++) {
		//Verifica os tres casos de posição invalida
		vernum = verifica_casos_letra (vetor_ver, i, j, matrix [i] [j], tam, ver_num, ver_colunas);
		if (vernum == 0) {
			continue;
		}
		//Monta o vetor com as posições das damas
		vetor_ver [i].lin = i;
		vetor_ver [i].col = j;
		ver_num [(int) matrix [i] [j]-65] = 1;
		ver_colunas [j] = 1;
		//Chegou ao final e deu veradde nos 3 testes
		if (vernum == 1 && i == tam-1){
			return 1;
		}
		//Não esta no final e chama recursivamente para a proxima linha
		else if (vernum == 1){
			ver = ver_pos_letra (matrix, vetor_ver, i, tam, ver_num, ver_colunas);
			ver_num [(int) matrix [i] [j]-65] = 0;
			ver_colunas [j] = 0;
			if (ver == 1) {
				return 1;
			}
		}
	}

	return 0;
}

int verifica_casos_letra (ver_ver *vetor_ver,int i, int j, char p, int tam, char ver_num [], char ver_colunas []) {
	int z;

	//Caso da rainha na mesma posição
	if (ver_num [(int) p - 65] == 1){
		return 0;
	}

	//Caso da coluna
	if (ver_colunas [j] == 1){
		return 0;
	}

	for (z=0; z<i; z++) {
		//Caso da diagonal
		if (abs(vetor_ver [z].col - j) == abs(vetor_ver [z].lin - i)) {
			return 0;
		}
	}

	return 1;
}

int set_linha1_numero (char **matrix, ver_ver *vetor_ver, int tam, char ver_num [], char ver_colunas []) {
	int j, i, ver;

	//Seleciona a primeira linha
	i = 0;

	//Seleciona um elemento da primeira linha, e chama ver_pos para verificar
	//os elementos da segunda linha, qual deles pode ser utilizado para continar
	//testando, ou seja qual deles tem posição valida
	for (j=0; j<tam; j++) {
		//Monta o vetor com as posições das damas
		vetor_ver [i].lin = i;
		vetor_ver [i].col = j;
		ver_num [(int) matrix [i] [j]] = 1;
		ver_colunas [j] = 1;
		//Chama a verificação da segunda linha
		ver = ver_pos_numero (matrix, vetor_ver, i, tam, ver_num, ver_colunas);
		ver_num [(int) matrix [i] [j]] = 0;
		ver_colunas [j] = 0;
		if (ver == 1)
			return 1;
	}
	return 0;
}

int ver_pos_numero (char **matrix, ver_ver *vetor_ver, int i, int tam, char ver_num [], char ver_colunas []) {
	int vernum, ver;
	int j;

	//Desce de linha
	i++;

	for (j=0; j<tam; j++) {
		//Verifica os tres casos de posição invalida
		vernum = verifica_casos_numero (vetor_ver, i, j, matrix [i] [j], tam, ver_num, ver_colunas);
		if (vernum == 0) {
			continue;
		}
		//Monta o vetor com as posições das damas
		vetor_ver [i].lin = i;
		vetor_ver [i].col = j;
		ver_num [(int) matrix [i] [j]] = 1;
		ver_colunas [j] = 1;
		//Chegou ao final e deu verdade nos 3 testes
		if (vernum == 1 && i == tam-1){
			return 1;
		}
		//Não esta no final e chama recursivamente para a proxima linha
		else if (vernum == 1){
			ver = ver_pos_numero (matrix, vetor_ver, i, tam, ver_num, ver_colunas);
			ver_num [(int) matrix [i] [j]] = 0;
			ver_colunas [j] = 0;
			if (ver == 1) {
				return 1;
			}
		}
	}

	return 0;
}

int verifica_casos_numero (ver_ver *vetor_ver,int i, int j, char p, int tam, char ver_num [], char ver_colunas []) {
	int z;
	
	//Caso da rainha na mesma posição
	if (ver_num [(int) p] == 1){
		return 0;
	}

	//Caso da coluna
	if (ver_colunas [j] == 1){
		return 0;
	}

	for (z=0; z<i; z++) {
		//Caso da diagonal
		if (abs(vetor_ver [z].col - j) == abs(vetor_ver [z].lin - i)) {
			return 0;
		}
	}

	return 1;
}

void print_nao () {
	printf("Sem solucao.\n");
	return;
}

void print_tem () {
	printf("Tem solucao.\n");
	return;
}

void free_mem (char **matrix, int tam) {
	int i;

	for (i=0; i<tam; i++) {
		free (matrix [i]);
	}

	return;
}