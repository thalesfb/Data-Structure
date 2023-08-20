#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct 
{
    char nome[30];
    int ano_nasc;
    int n_filhos;
    float salario;
} IRPF;

IRPF* alocaMemoria(int);
void carregaVetor(IRPF*, int);
void escreveVetor(IRPF*, int);
void liberaMemoria(IRPF*);

//função que aloca dinamicamente a memoria retornando um ponteiro
IRPF* alocaMemoria(int tam){
    if (tam > 1)
    {
        return (IRPF*) malloc(sizeof(IRPF)* tam);    
    }
    else
    {
        printf("Tamanho do vetor precisa ser maior que 1!\n");
        return NULL;
    }
}

void carregaVetor(IRPF* irpf, int tam){
    int i;
    printf("%i\n", tam);

    for (i = 0; i < tam; i++)
    {
        printf ("Digite o nome da %ia pessoa: ", (i + 1));
        //getchar();
        fflush(stdin);
        //system("pause");
        scanf("%[^\n]s", irpf[i].nome);
        irpf[i].ano_nasc = (int) rand() % 100;
        irpf[i].n_filhos = (int) rand() % 10;
        irpf[i].salario = rand() % 100000;
    }
}

void escreveVetor(IRPF* irpf, int tam){
    int i;
    for (i = 0; i < tam; i++)
    {
        printf("ID pessoa: %i\t", i);
        printf("Nome: %s\t", irpf[i].nome);
        printf("Ano de nascimento: %i\t", irpf[i].ano_nasc);
        printf("Número de filhos: %i\t", irpf[i].n_filhos);
        printf("Salário: %f\n", irpf[i].salario);
    }
}

void liberaMemoria(IRPF* irpf){
    free(irpf);
}

int main(){
    srand(time(NULL));
    IRPF* irpf;
    int tam;
    printf("Digite a quantidade de pessoas: ");
    scanf("%i", &tam);

    irpf = alocaMemoria(tam);
    printf("%i\n", tam);
    if (irpf == NULL)
    {
        printf("Memória não alocada, processo abortado.\n");
        return -1;
    }
    
    carregaVetor(irpf, tam);
    escreveVetor(irpf, tam);
    liberaMemoria(irpf);

    return 0;
}