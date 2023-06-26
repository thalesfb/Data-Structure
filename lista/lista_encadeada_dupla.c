#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct sNodo {
    char dado[100];
    struct sNodo* next;
    struct sNodo* prev;
} Nodo;
typedef struct sLista {
    struct sNodo* head;
    struct sNodo* tail;
    int size;
} Lista;

void liberaMemoriaNodo(Nodo*);
Nodo* alocaMemoriaNodo();
Nodo* criaNodo(char*);
Lista* alocaMemoriaLista();
void percorreListaHeadTail(Lista*);
void percorreListaTailHead(Lista*);
int insereElementoLista(Lista*, Nodo*, char*);
Nodo* removeElementoLista(Lista*, Nodo*);
Lista* criaLista();
Nodo* buscaLista(Lista*, char*);
void liberaMemoriaLista(Lista*);


void liberaMemoriaNodo(Nodo* no) {
    free(no);
}

Nodo* alocaMemoriaNodo() {
    return (Nodo*)malloc(sizeof(Nodo));
}

Nodo* criaNodo(char* dado) {
    Nodo* no = alocaMemoriaNodo();
    if (no != NULL)
    {
        strcpy(no->dado, dado);
        no->prev = NULL;
        no->next = NULL;
    }
    return no;
}

Lista* alocaMemoriaLista(Lista* lista) {
    return (Lista*)malloc(sizeof(Lista));
}

void percorreListaHeadTail(Lista* lista) {
    Nodo* no = lista->head;

    while (no != NULL)
    {
        printf("%s \t", no->dado);
        no = no->next;
    }
}

void percorreListaTailHead(Lista* lista) {
    Nodo* no = lista->tail;

    while (no != NULL)
    {
        printf("%s \t", no->dado);
        no = no->prev;
    }
}

int insereElementoLista(Lista* lista, Nodo* pivo, char* dado) {
    Nodo* novo = criaNodo(dado);
    if (novo == NULL) {
        printf("Erro ao criar novo nodo!\n");
        return -1;
    }
    if ((pivo == NULL) && (lista->size != 0))
    {
        printf("Erro ao inserir elemento na lista!\n");
        return -2;
    }
    if (lista->size == 0) {
        lista->head = novo;
        lista->tail = novo;
    }
    else {
        novo->next = pivo->next;
        novo->prev = pivo;

        if (pivo->next == NULL) {
            lista->tail = novo;
        }
        else {
            pivo->next->prev = novo;
        }
        pivo->next = novo;
    }
    lista->size++;
    return 0;
}

Nodo* removeElementoLista(Lista* lista, Nodo* elemento) {
    if ((elemento != NULL) && (lista->size != 0))
    {
        if (elemento == lista->head)
        {
            lista->head = elemento->next;
            if (lista->head == NULL) {
                lista->tail = NULL;
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
                lista->tail = elemento->prev;
            }
            else
            {
                elemento->next->prev = elemento->prev;
            }
        }
        lista->size--;
        return elemento;
    }
    return NULL;
}
Lista* criaLista() {
    Lista* lista = alocaMemoriaLista(lista);
    if (lista != NULL)
    {
        lista->head = NULL;
        lista->tail = NULL;
        lista->size = 0;
    }
    return lista;
}
Nodo* buscaLista(Lista* lista, char* dado) {
    Nodo* no = lista->head;

    while (no != NULL) {
        if (strcmp(no->dado, dado) == 0) {
            printf("%s\t", no->dado);
            return no;
        }
        no = no->next;
    }
    return NULL;
}
void liberaMemoriaLista(Lista* lista) {
    Nodo* no = lista->head;
    Nodo* aux;

    while (no != NULL)
    {
        aux = no;
        no = no->next;
        liberaMemoriaNodo(aux);
    }
    free(lista);
}