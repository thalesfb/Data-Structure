#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hash/hash.c"

FILE* abrirArquivo(char*);
TabelaHash* construirTabelaHash();
void salvarTabelaHashCSV(TabelaHash*);
void salvarQtdTabelaHashCSV(TabelaHash*);
int numeroPrimoAleatorio();

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
int numeroPrimoAleatorio() {
  int n = rand() % 1000;
  while (1) {
    int primo = 1;
    for (int i = 2; i < n; i++) {
      if (n % i == 0) {
        primo = 0;
        break;
      }
    }
    if (primo == 1) {
      printf("Número primo aleatório: %d\n", n);
      return n;
    }
    n++;
  }
}

int main() {
  char nome[100];
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
  int opcao = 0;
  printf("O que deseja fazer?\n");
  printf("1 - Imprimir tabela hash\n");
  printf("2 - Buscar nome\n");
  printf("3 - Remover nome\n");
  printf("4 - Inserir nome\n");
  printf("5 - Escolher número primo aleatorio para M\n");
  printf("6 - Imprimir tabela hash em arquivo CSV\n");
  printf("0 - Sair\n");
  printf("Opção: ");
  scanf("%d", &opcao);
  switch (opcao)
  {
  case 1:
    printf("Imprimindo tabela hash...\n");
    imprimeTabelaHash(tabela, m);
    break;
  case 2:
    printf("Qual nome deseja buscar: ");
    scanf("%s", nome);
    buscaTabelaHash(tabela, nome, m);
    break;
  case 3:
    printf("Qual nome deseja remover: ");
    scanf("%s", nome);
    removeTabelaHash(tabela, nome, m);
    break;
  case 4:
    printf("Qual nome deseja inserir: ");
    scanf("%s", nome);
    insereTabelaHash(tabela, nome, m);
    break;
  case 5:
    printf("Escolhendo número primo aleatorio para M...\n");
    m = numeroPrimoAleatorio();
    printf("Novo valor de M: %d\n", m);
    break;
  case 6:
    printf("Imprimindo tabela hash em arquivo CSV...\n");
    tabela = construirTabelaHash(arquivoBusca, m);
    salvarTabelaHashCSV(tabela);
    salvarQtdTabelaHashCSV(tabela);
    break;
  case 0:
    printf("Saindo...\n");
    liberaTabelaHash(tabela, m);
    break;
  default:
    printf("Opção inválida!\n");
    break;
  }
}