#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PRETA 0
#define BRANCA 0xFFFFFF

typedef struct {
    int w, h;
    int **pix;
} Img;

typedef struct Lista 
{
    int i, j;
    int cor;
    int distancia;
    struct Lista *prox;
}Lista;

Img *ler_img();
void salvar_img(Img * img, char *file);
void libera_img(Img *img);
int procuraVizinhos (int i, int j, int corRegiao, Img *img, int distanciaPoint, Lista *inicioLista, Lista **fimLista);

// exemplo de como usar as funções:
// lê uma imagem e cria um novo
// arquivo com metade da imagem pintada
int main(int argc, char *argv[]) {
    int i, j;
    int flag = 0;
    
    Img *img = ler_img();
    salvar_img(img, "pintada.ppm");

    // for (i = 0; i < img->h; i++)
    //     for (j = 0; j < img->w; j++)
    //         printf("%d\n", img->pix [i] [j]);

    //Procura uma regiao branca
    for (i = 0; i < img->h; i++){
        for (j = 0; j < img->w; j++){
            if (img->pix[i][j] == 16777215){
            flag = 1;
            break;
            }
        }
        if (flag == 1) {
            break;
        } 
    }

    //Seta o brancoI e brancoJ como um ponto da região inicial
    //Lista que armazena os membros a serem visitados, os elementos entram e saem
    //na forma de fila.
    Lista *inicioLista;
    Lista *fimLista;
    Lista *auxRemove;
    int retornoProcuraVizinhos = 0;


    inicioLista = (Lista *) malloc (sizeof (Lista));
    inicioLista->i = i;
    inicioLista->j = j;
    inicioLista->distancia = 0;
    inicioLista->cor = 16777215;
    inicioLista->prox = NULL;

    fimLista = inicioLista;

    while (retornoProcuraVizinhos == 0)
    {
        if (img->pix [inicioLista->i] [inicioLista->j] != -1)
            retornoProcuraVizinhos = procuraVizinhos (inicioLista->i, inicioLista->j, inicioLista->cor, img, inicioLista->distancia, inicioLista, &fimLista);

        if (retornoProcuraVizinhos != 0)
            break;

        //if (inicioLista->prox != NULL) 
        {
            auxRemove = inicioLista;
            inicioLista = inicioLista->prox;
            free (auxRemove);
        }
    }
    
    while (inicioLista != NULL) {
        auxRemove = inicioLista;
        inicioLista = inicioLista->prox;
        free (auxRemove);
    }

    printf("Maria deve memorizar %d regioes.\n", retornoProcuraVizinhos);

    libera_img(img);
    return 0;
}

int procuraVizinhos (int i, int j, int corRegiao, Img *img, int distanciaPoint, Lista *inicioLista, Lista **fimLista) 
{

    int verificaRetorno = 0;

    if (img->pix [i] [j] == 16777215 && distanciaPoint != 0) 
    {
        return 1;
    }

    if (img->pix [i] [j] != corRegiao && img->pix [i] [j] != -1 ) 
    {
        (*fimLista)->prox = (Lista *) malloc (sizeof (Lista));
        (*fimLista)->prox->i = i;
        (*fimLista)->prox->j = j;
        (*fimLista)->prox->distancia = distanciaPoint + 1;
        (*fimLista)->prox->cor = img->pix [i] [j];
        (*fimLista)->prox->prox = NULL;
        (*fimLista) = (*fimLista)->prox;
    }

    //Percorre a região, e marca a região como visitada
    if (img->pix [i] [j] == corRegiao) 
    {
        img->pix [i] [j]= -1;
        if (j+1 < img->w && img->pix [i] [j+1] != -1) 
        {
            verificaRetorno = procuraVizinhos (i, ++j, corRegiao, img, distanciaPoint, inicioLista, fimLista);
            j--;
            if (verificaRetorno != 0)
                return distanciaPoint;
        }
        if (i+1 < img->h && img->pix [i+1] [j] != -1) 
        {
            verificaRetorno = procuraVizinhos (++i, j, corRegiao, img, distanciaPoint, inicioLista, fimLista);
            i--;        
             if (verificaRetorno != 0)
                return distanciaPoint;
        }
        if (j-1 >= 0 && img->pix [i] [j-1] != -1) 
        {
            verificaRetorno = procuraVizinhos (i, --j, corRegiao, img, distanciaPoint, inicioLista, fimLista);
            j++;
             if (verificaRetorno != 0)
                return distanciaPoint;
        }
        if (i-1 >= 0 && img->pix [i-1] [j] != -1) 
        {
            verificaRetorno = procuraVizinhos (--i, j, corRegiao, img, distanciaPoint, inicioLista, fimLista);
            i++;
             if (verificaRetorno != 0)
                return distanciaPoint;
        }
    }

    if (verificaRetorno != 0)
        return distanciaPoint;

    return 0;
}

// função presume que não ocorrem erros e que 
// máximo valor de valor de um canal de cor é 255
Img *ler_img() {
    Img *img;
    char peek;
    int i, j, r, g, b;
    assert(img = malloc(sizeof(*img)));
    scanf("P3 ");
    while((peek = getchar()) == '#') scanf("%*[^\r\n]%*[\r\n]");
    ungetc(peek,stdin);
    assert(scanf("%d %d %*d", &img->w, &img->h)==2);
    assert(img->pix = malloc(sizeof(*img->pix) * img->h));
    for (i = 0; i < img->h; i++) {
        assert(img->pix[i] = malloc(sizeof(**img->pix) * img->w));
        for (j = 0; j < img->w; j++) {
            assert(scanf("%d%d%d", &r, &g, &b)==3);
            img->pix[i][j] = (r << 16) + (g << 8) + b;
        }
    }
    return img;
}
void salvar_img(Img * img, char *file) {
    int i, j;
    FILE *fp = fopen(file, "w");
    fprintf(fp, "P3\n%d %d %d\n", img->w, img->h, 255);
    for (i = 0; i < img->h; i++) {
        for (j = 0; j < img->w; j++) {
            int r, g, b;
            int pix = img->pix[i][j];
            r = pix >> 16 & 0xFF;
            g = pix >> 8  & 0xFF;
            b = pix       & 0xFF;
            fprintf(fp, "%d %d %d\n",  r, g, b);
        }
    }
    fclose(fp);
}
void libera_img(Img *img) {
    int i;
    for (i = 0; i < img->h; i++)
        free(img->pix[i]);
    free(img->pix);
    free(img);
}




