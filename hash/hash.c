#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lista/lista_encadeada_dupla.c"

typedef struct sTabelaHash {
  Lista** hash;
  int size;
} TabelaHash;

int comparastrings(const void* a, const void* b);
TabelaHash* criaTabelaHash(int);
void liberaTabelaHash(TabelaHash*, int);
int funcaoHash(int, int);
int funcaoHashString(char*, int);
int insereTabelaHash(TabelaHash*, char*, int);
void imprimeTabelaHash(TabelaHash*, int);
void removeTabelaHash(TabelaHash*, char*, int);
int buscaTabelaHash(TabelaHash*, char*, int);
int qtdElementosChave(TabelaHash*, int);
void ordenaElementosChave(TabelaHash*, int);

int comparastrings(const void* a, const void* b) {
  const char* str_a = *(const char**)a;
  const char* str_b = *(const char**)b;
  return strcmp(str_a, str_b);
}

TabelaHash* criaTabelaHash(int m) {
  TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
  if (tabela == NULL) {
    printf("Erro ao alocar memória para a tabela hash\n");
    return NULL;
  }
  tabela->hash = (Lista**)malloc(sizeof(Lista*) * m);
  if (tabela->hash == NULL) {
    printf("Erro ao alocar memória para a tabela hash\n");
    return NULL;
  }
  for (int i = 0; i < m; i++) {
    tabela->hash[i] = criaLista();
  }
  tabela->size = m;
  return tabela;
}

void liberaTabelaHash(TabelaHash* tabela, int m) {
  for (int i = 0; i < m; i++) {
    liberaMemoriaLista(tabela->hash[i]);
  }
  free(tabela->hash);
  free(tabela);
}

int funcaohash(int chave, int m) {
  return chave % m;
}

int funcaoHashString(char* chave, int m) {
  int soma = 0;
  for (int i = 0; i < strlen(chave); i++) {
    soma += chave[i];
  }
  return funcaohash(soma, m);
}

int insereTabelaHash(TabelaHash* tabela, char* nome, int m) {
  int chave = funcaoHashString(nome, m);
  if (insereElementoLista(tabela->hash[chave], tabela->hash[chave]->tail, nome) != 0) {
    printf("Erro ao inserir elemento na tabela hash\n");
    return 1;
  }
  ordenaElementosChave(tabela, chave);
  return 0;
}

void imprimeTabelaHash(TabelaHash* tabela, int m) {
  for (int i = 0; i < m; i++) {
    printf("Chave %d: ", i);
    percorreListaHeadTail(tabela->hash[i]);
    printf("\n");
  }
}

void removeTabelaHash(TabelaHash* tabela, char* nome, int m) {
  int chave = funcaoHashString(nome, m);
  if (buscaTabelaHash(tabela, nome, m) == 0) {
    removeElementoLista(tabela->hash[chave], buscaLista(tabela->hash[chave], nome));
  }
}

int buscaTabelaHash(TabelaHash* tabela, char* nome, int m) {
  int chave = funcaoHashString(nome, m);
  Nodo* no = buscaLista(tabela->hash[chave], nome);
  if (no != NULL) {
    printf("Nome encontrado na chave %d\n", chave);
    return 0;
  }
  else {
    printf("Nome não encontrado\n");
    return 1;
  }
}

int qtdElementosChave(TabelaHash* tabela, int chave) {
  return tabela->hash[chave]->size;
}

void ordenaElementosChave(TabelaHash* tabela, int chave) {
  int size = tabela->hash[chave]->size;
  char** array = malloc(size * sizeof(char*));
  Nodo* nodo = tabela->hash[chave]->head;
  for (int i = 0; nodo != NULL; i++) {
    array[i] = strdup(nodo->dado);
    nodo = nodo->next;
  }
  qsort(array, size, sizeof(char*), comparastrings);

  nodo = tabela->hash[chave]->head;
  for (int j = 0; nodo != NULL; j++) {
    strcpy(nodo->dado, array[j]);
    free(array[j]);
    nodo = nodo->next;
  }
  free(array);
}