#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 10
#define m 10

int** alocaMemoria(int, int);
void carregaMatriz (int**, int, int);
void escreveMatriz(int**, int, int);
void liberaMemoria(int**, int);

int main()
{
    srand(time(NULL));
    int** ma;
    ma = alocaMemoria(n, m);
    carregaMatriz (ma, n, m);
    escreveMatriz (ma, n, m);
    liberaMemoria(ma, n);
}

int** alocaMemoria(int linhas, int colunas)
{
    int** ma, lin;
    ma = (int**) malloc(sizeof(int*) * linhas);

    for (lin = 0; lin < linhas; lin++)
    {
        ma[lin] = (int*) malloc(sizeof(int) * colunas);
    }
    return ma;
}

void carregaMatriz(int** ma, int linhas, int colunas)
{
    int l, c;

    for (l = 0; l < linhas; l++)
    {
        for (c = 0; c < colunas; c++)
        {
            ma[l][c] = rand() % 100;
        }
    }
}

void escreveMatriz(int** ma, int linhas, int colunas)
{
    int l, c;

    for (l = 0; l < linhas; l++)
    {
        for (c = 0; c < colunas; c++)
        {
            printf("%i, ", ma[l][c]);
        }
    }
}
void liberaMemoria(int ** ma, int linhas)
{
    int lin;

    for (lin = 0; lin < linhas; lin++)
    {
        free(ma[lin]);
    }

    free(ma);
    
}