#ifndef filas_tradicionais_h
#define fila_tradicionais_h

#include <stdbool.h>

typedef struct sNodo {
  int dado;
  struct sNodo* next;
  struct sNodo* prev;
} Nodo;

typedef struct sFila {
  struct sNodo* front;
  struct sNodo* rear;
  int size;
} Fila;

Nodo* criaNodo(int dado);
Fila* criaFila();
int insereElementoFila(Fila* fila, int dado);
Nodo* removeElementoFila(Fila* fila);
Nodo* buscaFila(Fila* fila, int dado);
bool filaVazia(Fila* fila);
void percorreFilaHeadTail(Fila* fila);
void percorreFilaTailHead(Fila* fila);
void testeFila();

#endif // filas_tradicionais_h
