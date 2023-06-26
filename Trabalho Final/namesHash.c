#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hash/hash.c"

FILE* abrirArquivo(char*);
TabelaHash* construirTabelaHash();
void salvarTabelaHashCSV(TabelaHash*);
void salvarQtdTabelaHashCSV(TabelaHash*);

FILE* abrirArquivo(char* arquivoBusca) {
  FILE* arquivo = fopen(arquivoBusca, "r");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo!\n");
    exit(1);
  }
  return arquivo;
}

TabelaHash* construirTabelaHash(char* arquivoBusca, int m) {
  TabelaHash* tabela = criaTabelaHash(m);
  FILE* arquivo = abrirArquivo(arquivoBusca);
  char nome[50];
  while (fscanf(arquivo, "%s", nome) != EOF) {
    insereTabelaHash(tabela, nome, m);
  }
  fclose(arquivo);
  return tabela;
}

void salvarTabelaHashCSV(TabelaHash* tabela) {
  char output_file_name[100];
  sprintf(output_file_name, "tabela_hashM%d.csv", tabela->size);
  FILE* arquivo = fopen(output_file_name, "w");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo!\n");
    exit(1);
  }
  for (int i = 0; i < tabela->size; i++) {
    fprintf(arquivo, "%d,", i);
    Nodo* nodo = tabela->hash[i]->head;
    while (nodo != NULL) {
      if (nodo->next == NULL) {
        fprintf(arquivo, "%s", nodo->dado);
      }
      else
      {
        fprintf(arquivo, "%s,", nodo->dado);
      }
      nodo = nodo->next;
    }
    fprintf(arquivo, "\n");
  }
  fclose(arquivo);
}

void salvarQtdTabelaHashCSV(TabelaHash* tabela) {
  char output_file_name[100];
  sprintf(output_file_name, "qtd_tabela_hashM%d.csv", tabela->size);
  FILE* arquivo = fopen(output_file_name, "w");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo!\n");
    exit(1);
  }
  for (int i = 0; i < tabela->size; i++) {
    fprintf(arquivo, "%d,%d\n", i, tabela->hash[i]->size);
  }
  fclose(arquivo);
}

int main() {
  printf("Trabalho Final - Tabela Hash\n");
  int m = 0;
  printf("Digite o valor de m: ");
  scanf("%d", &m);
  char arquivoBusca[50];
  strcpy(arquivoBusca, "nomes.txt");
  printf("Construindo tabela hash...\n");
  TabelaHash* tabela = construirTabelaHash(arquivoBusca, m);
  salvarTabelaHashCSV(tabela);
  salvarQtdTabelaHashCSV(tabela);
  liberaTabelaHash(tabela, m);
}