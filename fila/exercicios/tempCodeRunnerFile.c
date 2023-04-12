#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <inttypes.h>

typedef struct sNodo {
    int placa;
    int movimentacao;
    struct sNodo* next;
    struct sNodo* prev;
} Nodo;

typedef struct sFila {
    struct sNodo* front;
    struct sNodo* rear;
    int size;
    //char nomeFila[20];
} Fila;

//protótipos
void liberaMemoriaNodo(Nodo*);
Nodo* alocaMemoriaNodo();
Nodo* criaNodo(int placa, int movimentacao);
Fila* alocaMemoriaFila();
void percorreFilaFrontToRear(Fila*);
void percorreFilaRearToFront(Fila*);
int insereElementoFila(Fila*, int, int);
Nodo* removeElementoFila(Fila*);
Fila* criaFila();
Nodo* buscaFila(Fila*, int);
bool filaVazia(Fila*);
void testeFila();

int partidaCarro(int, Fila*, Fila*);
void chegadaCarro(int, Fila*, Fila*);
Fila* movimentaCarros(Fila*);

int main() {

    int opcao = 0, placa = 0;
    char entrada;
    Fila* estacionamento = criaFila();
    Fila* espera = criaFila();

    while (opcao != 3)
    {
        printf("\n\n");
        printf("Digite uma das opções abaixo:\n");
        printf("1 - Movimentação\n");
        printf("2 - Ver estacionamento\n");
        printf("3 - Sair\n");
        printf("Opção: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite a movimentação(C para chegada e P pra Partida): ");
            //fflush(stdin);
            scanf(" %c", &entrada);
            printf("Digite a placa do carro:");
            scanf("%d", &placa);
            if (entrada == 'C' || entrada == 'c')
            {
                if (estacionamento->size == 10)
                {
                    printf("Estacionamento cheio! Ficará no aguardo de uma vaga!");
                    insereElementoFila(espera, placa, 0);
                }
                else
                {
                    insereElementoFila(estacionamento, placa, 0);
                }
            }
            else if (entrada == 'P' || entrada == 'p')
            {
                if (partidaCarro(placa, estacionamento, espera) == 0)
                {
                    printf("Carro não encontrado!");
                }
            }
            else
            {
                printf("Entrada inválida!");
            }

            opcao = 0;
            break;
        case 2:
            printf("Estacionamento: ");
            percorreFilaFrontToRear(estacionamento);
            printf("\n");
            printf("Fila de espera: ");
            percorreFilaFrontToRear(espera);
            printf("\n");
            break;
        case 3:
            printf("Saindo...");
            exit(0);
            break;
        default:
            printf("Opção inválida!");
            break;
        }
    }
    return 0;
}

//implementação
void liberaMemoriaNodo(Nodo* no) {
    free(no);
}

Nodo* alocaMemoriaNodo() {
    return (Nodo*)malloc(sizeof(Nodo));
}

Nodo* criaNodo(int placa, int movimentacao) {
    Nodo* no = alocaMemoriaNodo();
    if (no != NULL)
    {
        no->placa = placa;
        no->movimentacao = movimentacao;
        no->prev = NULL;
        no->next = NULL;
    }
    return no;
}

Fila* alocaMemoriaFila() {
    return (Fila*)malloc(sizeof(Fila));
}

void percorreFilaFrontToRear(Fila* fila) {
    Nodo* no = fila->front;
    while (no != NULL)
    {
        printf("%i \t", no->placa);
        no = no->next;
    }
}
void percorreFilaRearToFront(Fila* fila) {
    Nodo* no = fila->rear;

    while (no != NULL)
    {
        printf("%i \t", no->placa);
        no = no->prev;
    }
}

int insereElementoFila(Fila* fila, int placa, int movimentacao) {
    Nodo* novo = criaNodo(placa, movimentacao);

    if (novo == NULL) {
        return -1; //retorna -1 quando não for possível alocar memória
    }
    if (fila->size == 0) {
        fila->front = novo;
        fila->rear = novo;
        printf("Estacionamento vazio, inserindo na extremidade norte do estacionamento!\n");
    }
    else {
        novo->next = NULL;
        novo->prev = fila->rear;
        fila->rear->next = novo;
        fila->rear = novo;
        printf("Inserindo na extremidade sul do estacionamento!\n");
    }
    fila->size++;
    return 0;
}

Nodo* removeElementoFila(Fila* fila) {
    if (fila->size == 0) {
        return NULL; //retorna NULL quando a fila estiver vazia
    }

    Nodo* removido = fila->front;
    fila->front = fila->front->next;

    if (fila->front != NULL) {
        fila->front->prev = NULL;
    }
    else {
        fila->rear = NULL;
    }
    fila->size--;
    return removido;
}

Fila* criaFila() {
    Fila* fila = alocaMemoriaFila();
    if (fila != NULL)
    {
        fila->front = NULL;
        fila->rear = NULL;
        fila->size = 0;
    }
    return fila;
}
Nodo* buscaFila(Fila* fila, int placa) {
    Nodo* no = fila->front;

    while (no != NULL) {
        if (no->placa == placa) {
            printf("Placa: %d encontrada!\n", no->placa);
            return no;
        }
        no = no->next;
    }
}

bool filaVazia(Fila* fila) {
    return (fila->size == 0);
}

void testeFila() {
    Fila* fila = criaFila();
    if (fila == NULL) {
        printf("Erro: Fila não foi criada.\n");
    }
    else {
        printf("Fila criada com sucesso.\n");
    }

    insereElementoFila(fila, 1, 0);
    insereElementoFila(fila, 2, 0);
    insereElementoFila(fila, 3, 0);

    if (fila->front->placa != 1 || fila->rear->placa != 3 || fila->size != 3) {
        printf("Erro: Inserção de elementos falhou.\n");
    }
    else {
        printf("Inserção de elementos passou no teste.\n");
    }

    Nodo* removido = removeElementoFila(fila);

    if (removido == NULL || removido->placa != 1 || fila->front->placa != 2 || fila->size != 2) {
        printf("Erro: Remoção de elementos falhou.\n");
    }
    else {
        printf("Remoção de elementos passou no teste.\n");
    }

    Nodo* procurado = buscaFila(fila, 2);

    if (procurado == NULL || procurado->placa != 2) {
        printf("Erro: Busca de elementos falhou.\n");
    }
    else {
        printf("Busca de elementos passou no teste.\n");
    }

    removeElementoFila(fila);
    removeElementoFila(fila);

    if (!filaVazia(fila)) {
        printf("Erro: Verificação de fila vazia falhou.\n");
    }
    else {
        printf("Verificação de fila vazia passou no teste.\n");
    }
}

int partidaCarro(int placa, Fila* estacionamento, Fila* espera) {

    Nodo* carro = buscaFila(estacionamento, placa);

    if (carro == NULL) {
        liberaMemoriaNodo(carro);
        Nodo* carro = buscaFila(espera, placa);
        if (carro == NULL) {
            printf("Carro com placa %d não encontrado.\n", placa);
            return 1;
        }
        removeElementoFila(espera);
        printf("Carro com placa %d removido da fila de espera.\n", placa);
    }
    else {
        Nodo* removido = removeElementoFila(estacionamento);
        printf("Carro com placa %d removido do estacionamento. Número de movimentações: %d\n", removido->placa, removido->movimentacao);
        estacionamento = movimentaCarros(estacionamento);
        liberaMemoriaNodo(removido);
        while (!filaVazia(espera) && estacionamento->size < 10) {
            Nodo* carroEspera = removeElementoFila(espera);
            if (carroEspera != NULL) {
                insereElementoFila(estacionamento, carroEspera->placa, carroEspera->movimentacao + 1);
                printf("Carro com placa %d removido da fila de espera e inserido no estacionamento. Número de movimentações: %d\n", carroEspera->placa, carroEspera->movimentacao);
                liberaMemoriaNodo(carroEspera);
            }
        }
    }
    return 0;
}

Fila* movimentaCarros(Fila* estacionamento) {
    Nodo* no = estacionamento->front;
    if (no != NULL) {
        while (no->next != NULL) {
            no->movimentacao++;
            no = no->next;
        }
    }
    return estacionamento;
}