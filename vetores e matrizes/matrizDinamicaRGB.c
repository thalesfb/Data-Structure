#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int r, g, b;
} RGB;

RGB** alocaMatriz(int, int);
void carregaMatriz(RGB**, int, int);
void escreveMatriz(RGB**, int, int);
void liberaMatriz(RGB**, int);

RGB** alocaMatriz(int linhas, int colunas){
    RGB** rgb;
    int l;
    rgb = (RGB**) malloc(sizeof(RGB*) * linhas);
    for (l = 0; l < linhas; l++)
    {
        rgb[l] = (RGB*) malloc(sizeof(RGB) * colunas);
    }
    return rgb;
}

void carregaMatriz(RGB** rgb, int linhas, int colunas){
    int l, c;

    for (l = 0; l < linhas; l++)
    {
        for (c = 0; c < colunas; c++)
        {
            rgb[l][c].r = rand() % 255;
            rgb[l][c].g = rand() % 255;
            rgb[l][c].b = rand() % 255;
        }
    }
}

void liberaMatriz(RGB** rgb, int linhas){
    int l;
    for (l = 0; l < linhas; l++)
    {
        free(rgb[l]);
    }
    free(rgb);
}

void escreveMatriz(RGB** rgb, int linhas, int colunas){
    int l, c;
    printf("\n");
    for (l = 0; l < linhas; l++)
    {
        printf("Cor %i: \n", l);
        for (c = 0; c < colunas; c++)
        {
            printf("R:%i\t", rgb[l][c].r);
            printf("G:%i\t", rgb[l][c].g);
            printf("B:%i\t", rgb[l][c].b);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    srand(time(NULL));
    int l, c;
    RGB** rgb;
    printf("Digite o número de linhas: ");
    scanf("%i", &l);
    printf("Digite o número de colunas: ");
    scanf("%i", &c);
    rgb = alocaMatriz(l, c);
    carregaMatriz(rgb, l, c);
    escreveMatriz(rgb, l, c);
    liberaMatriz(rgb, l);
}