#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 10

// typedef struct {
//     int r, g, b;
// } RGB;

int* alocaMemoria(int tam);
void carregaVetor(int* vet);
void escreverVetor(int* vet);
void liberaMemoria(int* vet);

int main()
{
    srand(time(NULL)); // chama função time e coloca em um seed randomico para gerar valores aleatórios
    int *vet;

    vet = alocaMemoria(n);
    liberaMemoria(vet);
    carregaVetor(vet);
    escreverVetor(vet);
    liberaMemoria(vet);
 
    /*//alocação dinâmica do vetor
    vet = (int*) malloc(sizeof(int) * n);

    //libera memória do vetor
    free(vet);

    //carregamento do vetor
    for(i = 0; i < n; i++)
    {
        vet[i] = rand() % 100;
    }

    //escrevendo o vetor
    for(i = 0; i < n; i ++)
    {
        printf("%i, ", vet[i]);
    }
    // int x, y, *p_x;

    // x = 0;
    // p_x = &x;
    // y = *p_x;

    // x = 10;
    // //p_x = (int*) 5;
    

    // printf("x = %i", x);
    // printf("\ny = %i", y);
    // printf("\np_x = %i", *p_x);
    // printf("\nx = %x", p_x);

    // /*int *idade;
    // printf(*idade);
    // system("pause");

    //libera memória do vetor
    free(vet);*/

    return 0;
}

int* alocaMemoria(int tam) //alocação dinâmica de memória
{
    return (int*) malloc(sizeof (int) * tam);
}

void escreverVetor(int* vet) //escrevendo o vetor dinâmico
{
    int i;
    for(i = 0; i<n; i++)
    {
        printf("%i, ", vet[i]);
    }
}

void liberaMemoria(int* vet) //libera memoria do vetor dinâmico
{
    free(vet);
}

void carregaVetor(int* vet) //carrega valores pro vetor dinâmico
{
    int i;
    for(i = 0; i < n; i++)
    {
        vet[i] = rand() % 100;
    }
}
