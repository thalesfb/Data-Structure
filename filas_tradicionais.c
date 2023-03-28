#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    int dado;
    struct sNodo* next;
    struct sNodo* prev;
} Nodo;

typedef struct sFila {
    struct sNodo* head;
    struct sNodo* tail;
    int size;
} Fila;

void liberaMemoriaNodo(Nodo*); // ok
Nodo* alocaMemoriaNodo(); // ok
Nodo* criaNodo(int dado); // ok
Fila* alocaMemoriaFila(); // ok
void percorreFilaHeadTail(Fila*); // ok
void percorreFilaTailHead(Fila*); // ok
int insereElementoFila(Fila*, Nodo*, int); // ok
Nodo* removeElementoFila(Fila*, Nodo*); // ok
Fila* criaFila(); // ok 
Nodo* buscaFila(Fila*, int);

int main() {
    Fila* fila1;

    //fila1 = alocaMemoriaFila(fila1);
    fila1 = criaFila();
    insereElementoFila(fila1, NULL, 10);
    insereElementoFila(fila1, fila1->head, 5);
    insereElementoFila(fila1, fila1->tail, 7);
    insereElementoFila(fila1, NULL, 19);
    insereElementoFila(fila1, fila1->head, 22);
    removeElementoFila(fila1, fila1->head);

    percorreFilaHeadTail(fila1);
    percorreFilaTailHead(fila1);
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

Fila* alocaMemoriaFila(Fila* fila) {
    return (Fila*)malloc(sizeof(Fila));
}

void percorreFilaHeadTail(Fila* fila) {
    Nodo* no = fila->head;

    while (no != NULL)
    {
        printf("%i \t", no->dado);
        no = no->next;
    }
}
void percorreFilaTailHead(Fila* fila) {
    Nodo* no = fila->tail;

    while (no != NULL)
    {
        printf("%i \t", no->dado);
        no = no->prev;
    }
}

int insereElementoFila(Fila* fila, Nodo* pivo, int dado) {
    Nodo* novo = criaNodo(dado);
    if (novo == NULL) {
        return -1; //retorna -1 quando não for possível alocar memória
    }
    if ((pivo == NULL) && (fila->size != 0))
    {
        return -2;
    }
    if (fila->size == 0) {
        fila->head = novo;
        fila->tail = novo;
    }
    else {
        novo->next = pivo->next;
        novo->prev = pivo;

        if (pivo->next == NULL) {
            fila->tail = novo;
        }
        else {
            pivo->next->prev = novo;
        }
        pivo->next = novo;
    }
    fila->size++;
}

Nodo* removeElementoFila(Fila* fila, Nodo* elemento) {
    if ((elemento != NULL) && (fila->size != 0))
    {
        if (elemento == fila->head)
        {
            fila->head = elemento->next;
            if (fila->head == NULL) {
                fila->tail = NULL;
            }
            else
            {
                elemento->next->prev = NULL;
            }
        }
        else
        {
            elemento->prev->next = elemento->next;
            if (elemento->next == NULL)
            {
                fila->tail = elemento->prev;
            }
            else
            {
                elemento->next->prev = elemento->prev;
            }
        }
        liberaMemoriaNodo(elemento);
        fila->size--;
    }
}
Fila* criaFila() {
    Fila* fila = alocaMemoriaFila(fila);
    if (fila != NULL)
    {
        fila->head = NULL;
        fila->tail = NULL;
        fila->size = 0;
    }
    return fila;
}
Nodo* buscaFila(Fila* fila, int dado) {
    Nodo* no = fila->head;

    while (no != NULL) {
        if (no->dado == dado) {
            //printf("%d\t", &no);
            return no;
        }
        no = no->next;
    }
}