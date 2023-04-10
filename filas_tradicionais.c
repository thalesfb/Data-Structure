#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <inttypes.h>

typedef struct sNodo {
    int dado;
    struct sNodo* next;
    struct sNodo* prev;
} Nodo;

typedef struct sFila {
    struct sNodo* front;
    struct sNodo* rear;
    int size;
    char nomeFila[20];
} Fila;

void liberaMemoriaNodo(Nodo*);
Nodo* alocaMemoriaNodo();
Nodo* criaNodo(int dado);
Fila* alocaMemoriaFila();
void percorreFilaHeadTail(Fila*);
void percorreFilaTailHead(Fila*);
int insereElementoFila(Fila*, int);
Nodo* removeElementoFila(Fila*);
Fila* criaFila();
Nodo* buscaFila(Fila*, int);
bool filaVazia(Fila*);
void testFila();

int main() {

    int opcao = 0, dado = 0;
    Fila* fila;
    //testFila();

    while (opcao != 6)
    {
        printf("\n\n");
        printf("Digite uma das opções abaixo:\n");
        printf("1 - Criar fila\n");
        printf("2 - Inserir elemento na fila\n");
        printf("3 - Remover elemento da fila\n");
        printf("4 - Buscar elemento na fila\n");
        printf("5 - Imprimir fila\n");
        printf("6 - Testar a fila\n");
        printf("7 - Sair\n");
        printf("Opção: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            fila = criaFila();
            printf("Nome da fila:");
            scanf("%s", fila->nomeFila);
            if (fila == NULL) {
                printf("Erro ao criar fila!");
            }
            else {
                printf("Fila %s criada com sucesso!", fila->nomeFila);
            }
            opcao = 0;
            break;
        case 2:
            printf("Digite o dado a ser inserido: ");
            scanf("%i", &dado);
            if (insereElementoFila(fila, dado) == 0)
            {
                printf("Elemento inserido com sucesso!");
            }
            else
            {
                printf("Erro ao inserir elemento!");
            }
            opcao = 0;
            break;
        case 3:
            if (filaVazia(fila)) {
                printf("Erro ao remover elemento! A fila está vazia!");
            }
            else
            {
                Nodo* removido = removeElementoFila(fila);
                printf("Elemento removido com sucesso: %d!", removido->dado);
                liberaMemoriaNodo(removido);
            }
            opcao = 0;
            break;
        case 4:
            printf("Digite o dado a ser buscado: ");
            scanf("%i", &dado);
            if (buscaFila(fila, dado) == NULL)
            {
                printf("Elemento não encontrado!");
            }
            opcao = 0;
            break;
        case 5:
            percorreFilaHeadTail(fila);
            opcao = 0;
            break;
        case 6:
            testFila();
            opcao = 0;
            break;
        case 7:
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

Nodo* criaNodo(int dado) {
    Nodo* no = alocaMemoriaNodo();
    if (no != NULL)
    {
        no->dado = dado;
        no->prev = NULL;
        no->next = NULL;
    }
    return no;
}

Fila* alocaMemoriaFila() {
    return (Fila*)malloc(sizeof(Fila));
}

void percorreFilaHeadTail(Fila* fila) {
    Nodo* no = fila->front;
    printf("Tamanho da %s: %i \n", fila->nomeFila, fila->size);
    printf("Fila %s: \n", fila->nomeFila);
    while (no != NULL)
    {
        printf("%i \t", no->dado);
        no = no->next;
    }
}
void percorreFilaTailHead(Fila* fila) {
    Nodo* no = fila->rear;

    printf("Fila %s: \n", fila->nomeFila);

    while (no != NULL)
    {
        printf("%i \t", no->dado);
        no = no->prev;
    }
}

int insereElementoFila(Fila* fila, int dado) {
    Nodo* novo = criaNodo(dado);

    if (novo == NULL) {
        return -1; //retorna -1 quando não for possível alocar memória
    }
    if (fila->size == 0) {
        fila->front = novo;
        fila->rear = novo;
        printf("Fila vazia, inserindo elemento na frente da fila!\n");
    }
    else {
        novo->next = NULL;
        novo->prev = fila->rear;
        fila->rear->next = novo;
        fila->rear = novo;
        printf("Inserindo elemento no final da fila!\n");
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
Nodo* buscaFila(Fila* fila, int dado) {
    Nodo* no = fila->front;

    while (no != NULL) {
        if (no->dado == dado) {
            printf("Fila %s\t dado: %d encontrado!\n", fila->nomeFila, no->dado);
            return no;
        }
        no = no->next;
    }
}

bool filaVazia(Fila* fila) {
    return (fila->size == 0);
}
void testFila() {
    Fila* fila = criaFila();
    strcpy(fila->nomeFila, "TesteFila");

    // Teste: inserção de elementos
    insereElementoFila(fila, 1);
    insereElementoFila(fila, 2);
    insereElementoFila(fila, 3);

    // Verificar se os elementos foram inseridos corretamente
    if (fila->front->dado != 1 || fila->rear->dado != 3 || fila->size != 3) {
        printf("Erro: Inserção de elementos falhou.\n");
    }
    else {
        printf("Inserção de elementos passou no teste.\n");
    }

    // Teste: remoção de elementos
    Nodo* removedNode = removeElementoFila(fila);

    // Verificar se o elemento removido é o correto e se a fila foi atualizada corretamente
    if (removedNode == NULL || removedNode->dado != 1 || fila->front->dado != 2 || fila->size != 2) {
        printf("Erro: Remoção de elementos falhou.\n");
    }
    else {
        printf("Remoção de elementos passou no teste.\n");
    }

    // Teste: busca de elementos
    Nodo* foundNode = buscaFila(fila, 2);

    // Verificar se o elemento buscado é o correto
    if (foundNode == NULL || foundNode->dado != 2) {
        printf("Erro: Busca de elementos falhou.\n");
    }
    else {
        printf("Busca de elementos passou no teste.\n");
    }

    // Teste: fila vazia
    removeElementoFila(fila);
    removeElementoFila(fila);

    if (!filaVazia(fila)) {
        printf("Erro: Verificação de fila vazia falhou.\n");
    }
    else {
        printf("Verificação de fila vazia passou no teste.\n");
    }
}
