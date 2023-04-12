#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
   int dado;
   struct sNodo* next;
} Nodo;

typedef struct sLista {
    struct sNodo* head;
    struct sNodo* tail;
    int size;
} Lista;

// prototipação
Nodo* alocaMemoriaNodo();
Nodo* criaNodo(int dado);

Lista* alocaMemoriaLista();
Lista* criaLista();
int insereElementoLista(Lista*, Nodo*, int);
Nodo* removeElementoLista(Lista*, Nodo*);
void percorreListaHeadTail(Lista*);
void liberaMemoriaNodo(Nodo*);

int main(){
    Lista* lista1;

    //lista1 = alocaMemoriaLista(lista1);
    lista1 = criaLista();
    insereElementoLista(lista1, NULL, 10);
    insereElementoLista(lista1, lista1->head, 5);
    insereElementoLista(lista1, lista1->tail, 7);
    insereElementoLista(lista1, NULL, 19);
    insereElementoLista(lista1, lista1->head, 22);
    removeElementoLista(lista1, lista1->head);

    percorreListaHeadTail(lista1);
    return 0;
}

//implementação
void liberaMemoriaNodo(Nodo* no){
    free(no);
}

Nodo* alocaMemoriaNodo(){
    return (Nodo*) malloc(sizeof(Nodo));
}

Lista* alocaMemoriaLista(){
    return (Lista*) malloc(sizeof(Lista));
}

Nodo* criaNodo(int dado){
    Nodo* nodo = alocaMemoriaNodo();
    if (nodo != NULL){
        nodo->dado = dado;
        nodo->next = NULL;
    }
        return nodo;
}

Lista* criaLista(){ // se fizer mais de uma lista?
    Lista* lista = alocaMemoriaLista();
    if (lista != NULL)
    {
        lista->head = NULL;
        lista->tail = NULL;
        lista->size = 0;
    }
        return lista;
}

int insereElementoLista(Lista* lista, Nodo* pivo, int dado){
    Nodo* novo = criaNodo(dado);
    if (novo == NULL){
        return -1; //retorna -1 quando não for possível alocar memória
    }
    if (pivo == NULL){
        if (lista->size == 0)
            lista->tail = novo;

        novo->next = lista->head;
        lista->head = novo;
    } else {
        if(pivo->next == NULL)
            lista->tail = novo;

        novo->next = pivo->next;
        pivo->next = novo;
    }
    lista->size++;
    return 0;
}
void percorreListaHeadTail(Lista* lista){
    Nodo* nodo = lista->head;

    while (nodo != NULL)
    {
        printf("%i \t", nodo->dado);
        nodo = nodo->next;
    }
}

Nodo* removeElementoLista(Lista* lista, Nodo* pivo){
    Nodo* antigo;
    int dado;

    if(lista->size == 0)
        return -1; // lista vazia
    if(pivo == NULL){
        antigo->next = lista->head;
        lista->head = antigo;
        // elemento_antigo = lista->head
		// lista->head = lista->head->next
        if (lista->head == NULL)
            lista->tail = NULL;
    } else if (pivo->next == NULL)
            return (int) -2; // o elemento é o final da lista

        // antigo = lista->head;
        // lista->head = lista->head->next;
        antigo = pivo->next;
		pivo->next = pivo->next->next;

        if (pivo->next == NULL)
			lista->tail = pivo;
	
        liberaMemoriaNodo(antigo);
        lista->size--;
        return antigo;
}


