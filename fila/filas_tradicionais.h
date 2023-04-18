#ifndef filas_tradicionais_h
#define fila_tradicionais_h

#include <stdbool.h>

typedef struct sNodo {
  int dado;
  int movimentacao;
  struct sNodo* next;
  struct sNodo* prev;
} Nodo;

typedef struct sFila {
  struct sNodo* front;
  struct sNodo* rear;
  int size;
} Fila;

void liberaMemoriaNodo(Nodo*);
Nodo* alocaMemoriaNodo();
Nodo* criaNodo(int dado);
Fila* criaFila();
Fila* alocaMemoriaFila();
int insereElementoFila(Fila* fila, int dado, int movimentacao);//ok
Nodo* removeElementoFila(Fila* fila);//ok
Nodo* buscaFila(Fila* fila, int dado);//ok
bool filaVazia(Fila* fila);//ok
void percorreFilaHeadTail(Fila* fila);//ok
void percorreFilaTailHead(Fila* fila);//ok
void testeFila();//ok
void liberaFila(Fila* fila);//ok

#endif // filas_tradicionais_h
