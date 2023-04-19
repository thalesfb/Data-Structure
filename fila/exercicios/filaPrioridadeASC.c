
/* Implemente uma fila de prioridade ascendente e suas operações, pqinsert,
pqmindelete e empty, usando cada um dos quatro métodos apresentados no texto.

Demonstre como classificar o conjunto de números de entrada (20, 13, 4, 2, 18, 40, 2, 19, 1)
 usando uma fila de prioridade ascendente e as operações pqinsert, pqmindelete e empty. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../filas_tradicionais.c"

int pqinsert(int, Fila*);
Nodo* pqmindelete(Fila*);
bool empty(Fila*);
void testeFilaPrioridade(Fila**);
void percorreFila(Fila*);

int main() {

  int opcao = 0, dado = 0;
  Fila* fila = criaFila();

  while (opcao != 5)
  {
    printf("\n\n");
    printf("Digite uma das opções abaixo:\n");
    printf("1 - Inserir elemento na fila\n");
    printf("2 - Remover elemento da fila\n");
    printf("3 - Imprimir fila\n");
    printf("4 - Testar a fila de prioridade\n");
    printf("5 - Sair\n");
    printf("Opção: ");
    scanf("%i", &opcao);

    switch (opcao)
    {
    case 1:
      printf("Digite o elemento a ser inserido na fila: ");
      scanf("%i", &dado);
      pqinsert(dado, fila);
      break;
    case 2:
      pqmindelete(fila);
      break;
    case 3:
      percorreFila(fila);
      break;
    case 4:
      testeFilaPrioridade(&fila);
      break;
    case 5:
      /*  if (empty(fila))
       {
         exit(0);
       } */
      liberaFila(fila);
      exit(0);
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
  }
}

int pqinsert(int dado, Fila* fila) {
  Nodo* novo = criaNodo(dado);
  Nodo* aux = fila->front;
  if (novo == NULL)
  {
    printf("Erro ao alocar memória!\n");
    return 0;
  }
  if (empty(fila))
  {
    fila->front = novo;
    fila->rear = novo;
    fila->size++;
  }
  else
  {
    while (aux != NULL)
    {
      if (aux->dado > dado)
      {
        if (aux->prev == NULL)
        {
          aux->prev = novo;
          novo->next = aux;
          fila->front = novo;
          fila->size++;
          return 1;
        }
        else
        {
          aux->prev->next = novo;
          novo->prev = aux->prev;
          aux->prev = novo;
          novo->next = aux;
          fila->size++;
          return 1;
        }
      }
      aux = aux->next;
    }
    fila->rear->next = novo;
    novo->prev = fila->rear;
    fila->rear = novo;
    fila->size++;
  }
  return 1;
}

Nodo* pqmindelete(Fila* fila) {
  Nodo* aux = fila->front;
  if (filaVazia(fila))
  {
    printf("Fila vazia!\n");
    return NULL;
  }
  else
  {
    fila->front = fila->front->next;
    if (fila->front != NULL)
    {
      fila->front->prev = NULL;
    }
    else
    {
      fila->rear = NULL;
    }
    fila->size--;
  }
  return aux;
}

bool empty(Fila* fila) {
  if (filaVazia(fila))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void percorreFila(Fila* fila) {
  Nodo* no = fila->front;
  if (no == NULL)
  {
    printf("Fila vazia!\n");
    return;
  }
  while (no != NULL)
  {
    printf("\nDado: %i", no->dado);
    no = no->next;
  }
  printf("\n");
}

void testeFilaPrioridade(Fila** fila) {
  int vetor[] = { 20, 13, 4, 2, 18, 40, 2, 19, 1 };
  int tamanho = sizeof(vetor) / sizeof(vetor[0]);
  for (int i = 0; i < tamanho; i++)
  {
    pqinsert(vetor[i], *fila);
    printf("\n");
    printf("Inserindo %i", vetor[i]);
  }
  printf("\n\n");
  percorreFila(*fila);
  printf("\n");
  for (int i = 0; i < tamanho; i++)
  {
    Nodo* removido = pqmindelete(*fila);
    printf("\n");
    printf("Removido: %i", removido->dado);
    free(removido);
  }
  printf("\n\n");
}