#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    int dado;
    struct sNodo* next;
    struct sNodo* prev;
} Nodo;

typedef struct sLista {
    struct sNodo* head;
    struct sNodo* tail;
    int size;
} Lista;

void liberaMemoriaNodo(Nodo*); // ok
Nodo* alocaMemoriaNodo(); // ok
Nodo* criaNodo(int dado); // ok
Lista* alocaMemoriaLista(); // ok
void percorreListaHeadTail(Lista*); // ok
void percorreListaTailHead(Lista*); // ok
int insereElementoLista(Lista*, Nodo*, int); // ok
Nodo* removeElementoLista(Lista*, Nodo*); // ok
Lista* criaLista(); // ok 
Nodo* buscaLista(Lista*, int);
void liberaMemoriaLista(Lista*);

/* int main() {
    Lista* lista1;

    //lista1 = alocaMemoriaLista(lista1);
    lista1 = criaLista();
    insereElementoLista(lista1, NULL, 10);
    insereElementoLista(lista1, lista1->head, 5);
    insereElementoLista(lista1, lista1->tail, 7);
    insereElementoLista(lista1, NULL, 19);
    insereElementoLista(lista1, lista1->head, 22);
    removeElementoLista(lista1, lista1->head);
    buscaLista(lista1, 7);
    buscaLista(lista1, 5);
    buscaLista(lista1, 22);

    percorreListaHeadTail(lista1);
    percorreListaTailHead(lista1);
    return 0;
} */

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

Lista* alocaMemoriaLista(Lista* lista) {
    return (Lista*)malloc(sizeof(Lista));
}

void percorreListaHeadTail(Lista* lista) {
    Nodo* no = lista->head;

    while (no != NULL)
    {
        printf("%i \t", no->dado);
        no = no->next;
    }
}
void percorreListaTailHead(Lista* lista) {
    Nodo* no = lista->tail;

    while (no != NULL)
    {
        printf("%i \t", no->dado);
        no = no->prev;
    }
}

int insereElementoLista(Lista* lista, Nodo* pivo, int dado) {
    Nodo* novo = criaNodo(dado);
    if (novo == NULL) {
        return -1; //retorna -1 quando não for possível alocar memória
    }
    if ((pivo == NULL) && (lista->size != 0))
    {
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
}

/* Nodo* removeElementoLista(Lista* lista, Nodo* elemento) {
    Nodo* no = lista->head;
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
        liberaMemoriaNodo(elemento);
        lista->size--;
        return no;
    }
} */
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
Nodo* buscaLista(Lista* lista, int dado) {
    Nodo* no = lista->head;

    while (no != NULL) {
        if (no->dado == dado) {
            printf("%d\t", &no);
            return no;
        }
        no = no->next;
    }
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