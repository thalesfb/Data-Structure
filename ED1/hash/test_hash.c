#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../hash/hash.c"
#define N 53

//protótipos
void test_criaTabelaHash(int);
void test_insercao_e_busca(TabelaHash*);
void test_removeTabelaHash(TabelaHash*);
void test_qtdElementosChave(TabelaHash*);
void test_liberaTabelaHash(TabelaHash*);

//implementações
void test_criaTabelaHash(int M) {
  TabelaHash* tabela = criaTabelaHash(N);
  assert(tabela != NULL);
  printf("Teste criaTabelaHash passou.\n");
}

void test_insercao_e_busca(TabelaHash* tabela) {
  char* nomes[] = { "João", "Maria", "Ana" };
  int num_nomes = sizeof(nomes) / sizeof(char*);
  for (int i = 0; i < num_nomes; i++) {
    assert(insereTabelaHash(tabela, nomes[i], N) == 0);
    Nodo* nodo = buscaTabelaHash(tabela, nomes[i], N);
    assert(nodo != NULL);
  }
  printf("Teste insercao_e_busca passou.\n");
}

void test_removeTabelaHash(TabelaHash* tabela) {
  removeTabelaHash(tabela, "João", M);
  Nodo* nodo = buscaTabelaHash(tabela, "João", N);
  assert(nodo == NULL);
  printf("Teste removeTabelaHash passou.\n");
}

void test_qtdElementosChave(TabelaHash* tabela) {
  int chaveMaria = funcaoHashString("Maria", N);
  int qtd = qtdElementosChave(tabela, chaveMaria);
  assert(qtd == 1);
  printf("Teste qtdElementosChave passou.\n");
}

void test_liberaTabelaHash(TabelaHash* tabela) {
  liberaTabelaHash(tabela, M);
  printf("Teste liberaTabelaHash passou.\n");
}

int main() {
  TabelaHash* tabela = criaTabelaHash(N);
  test_criaTabelaHash(N);
  test_insercao_e_busca(tabela);
  test_removeTabelaHash(tabela);
  test_qtdElementosChave(tabela);
  test_liberaTabelaHash(tabela);
  printf("Todos os testes passaram.\n");
  return 0;
}
