#include <stdio.h>
#include <stdlib.h>

typedef struct sNo {
  int chave;
  struct sNo* esq, * dir;
} No;

typedef struct {
  No* raiz;
} ABB;

//prototipacao
No* alocaMemoriaNo();
ABB* alocaMemoriaABB();
void liberaNo(No*);
void liberaArvore(ABB*);
No* criaNo(int);
ABB* criaArvore();
No* insere(No*, int);
No* insereArvore(ABB*, int);
No* busca(No*, int);
No* removeNo(No*, int);
No* menorValor(No*);
No* maiorValor(No*);
void remover(ABB*, int);
void imprime(ABB*);
void emOrdem(No*);
void preOrdem(No*);
void posOrdem(No*);

No* alocaMemoriaNo() {
  No* novo = (No*)malloc(sizeof(No));
  if (novo == NULL) {
    printf("Erro ao alocar memoria para o no!\n");
    exit(1);
  }
  return novo;
}

ABB* alocaMemoriaABB() {
  ABB* novo = (ABB*)malloc(sizeof(ABB));
  if (novo == NULL) {
    printf("Erro ao alocar memoria para a arvore!\n");
    exit(1);
  }
  return novo;
}

No* criaNo(int chave) {
  No* novo = alocaMemoriaNo();
  if (novo != NULL)
  {
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
  }
  return novo;
}

void liberaNo(No* no) {
  if (no != NULL) {
    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no);
  }
}

void liberaArvore(ABB* arvore) {
  if (arvore != NULL) {
    liberaNo(arvore->raiz);
    free(arvore);
  }
}

ABB* criaArvore() {
  ABB* novo = alocaMemoriaABB();
  if (novo == NULL) {
    printf("Erro ao alocar memoria para a arvore!\n");
    exit(1);
  }
  novo->raiz = NULL;
  return novo;
}

No* insere(No* no, int chave) {
  if (no == NULL) {
    return criaNo(chave);
  }
  else {
    if (chave <= no->chave) {
      no->esq = insere(no->esq, chave);
    }
    else {
      no->dir = insere(no->dir, chave);
    }
  }
  return no;
}

No* insereArvore(ABB* arvore, int chave) {
  arvore->raiz = insere(arvore->raiz, chave);
}

No* busca(No* raiz, int chave) {
  if (raiz->chave == chave) {
    printf("Chave %d encontrada/n", raiz->chave);
    return raiz;
  }
  if (chave < raiz->chave) {
    raiz->esq = busca(raiz->esq, chave);
  }
  else if (chave > raiz->chave) {
    raiz->dir = busca(raiz->dir, chave);
  }
}

No* removeNo(No* no, int chave) {
  if (no == NULL) {
    return no;
  }
  if (chave < no->chave) {
    no->esq = removeNo(no->esq, chave);
  }
  else if (chave > no->chave) {
    no->dir = removeNo(no->dir, chave);
  }
  else {
    if (no->esq == NULL) {
      No* aux = no->dir;
      free(no);
      return aux;
    }
    else if (no->dir == NULL) {
      No* aux = no->esq;
      free(no);
      return aux;
    }
    No* aux = menorValor(no->dir);
    no->chave = aux->chave;
    no->dir = removeNo(no->dir, aux->chave);
  }
}

No* menorValor(No* no) {
  No* aux = no;
  while (aux->esq != NULL) {
    aux = aux->esq;
  }
  return aux;
}

No* maiorValor(No* no) {
  No* aux = no;
  while (aux->dir != NULL) {
    aux = aux->dir;
  }
  return aux;
}

void remover(ABB* arvore, int chave) {
  removeNo(arvore->raiz, chave);
}

void imprime(ABB* arvore) {
  printf("Imprimindo em ordem:\n");
  emOrdem(arvore->raiz);
  printf("\nImprimindo em pre ordem:\n");
  preOrdem(arvore->raiz);
  printf("\nImprimindo em pos ordem:\n");
  posOrdem(arvore->raiz);
  printf("\n");
}

void emOrdem(No* raiz) {
  if (raiz != NULL) {
    emOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    emOrdem(raiz->dir);
  }
}

void preOrdem(No* raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->chave);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}

void posOrdem(No* raiz) {
  if (raiz != NULL) {
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf("%d ", raiz->chave);
  }
}

int main() {

  ABB* arvore = criaArvore();
  insereArvore(arvore, 12);
  insereArvore(arvore, 15);
  insereArvore(arvore, 14);
  insereArvore(arvore, 16);
  insereArvore(arvore, 10);
  insereArvore(arvore, 9);
  insereArvore(arvore, 12);

  busca(arvore->raiz, 16);

  insereArvore(arvore, 13);
  insereArvore(arvore, 11);
  insereArvore(arvore, 8);

  imprime(arvore);

  removeNo(arvore->raiz, 10);
  imprime(arvore);

  //                  12
  //          10          15
  //       9      12   14      16
  //    8    11      13

  liberaArvore(arvore);
  return 0;
}