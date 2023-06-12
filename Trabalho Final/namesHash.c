/*Trabalho Final : Implementação de uma Tabela de Espalhamento(Tabela Hash)

Instruções gerais
Resolver seguindo obrigatoriamente as regras abaixo :

Utilizar, obrigatoriamente, lista encadeada dupla
Implementar inserção, consulta, quantidade de elementos por chave, remoção, etc
Considerar tratamento de colisão.Para isto analisar a tabela hash gerada considerando as questões :

Quando deveria ser implementado tratamento de colisão ?
Como poderia ser esta implementação ?
Qual sua avaliação da tabela hash gerado em relação a hipótese do hashing uniforme ?
Qual sua análise em relação ao histograma de frequência de cada uma das chaves da tabela hash ?

Implementar ordenação dos elementos sob uma chave(OBS : para a ordenação deverá ser utilizado o método quicksort ou outro de complexidade algorítmica equivalente.
Implementar obrigatoriamente hashing com encadeamento.
Usar a base de dados com 100.788 nomes de brasileiros fornecida pelo professor.
A quantidade de chaves(m) deverá ser igual a 53 e a função de hash será de livre escolha do estudante.Considere para a sua escolha o referencial teórico apresentado na aula.OBS : não esqueça de justificar suas escolhas no relatório final!
Importante questão a ser respondida é : a hipótese do hashing uniforme foi alcançada ?
Demonstrar a distribuição dos nomes em cada uma das chaves utilizando um histograma e explicar o que o histograma está apresentando.

OBS 1 : Apresentar, além do código, pequeno relatório descrevendo o método(metodologia) utilizado para resolver o problema.O relatório deverá conter um resumo em torno de 500 a 800 palavras, figuras e gráficos que demonstrem a resolução e resultados obtidos(Fazer no próprio descritivo do GitHub).

OBS 2 : Utilizar o GitHub para entrega do trabalho final. Apresentação até 26 / 06, que será o último prazo (improrrogável).


Exemplo de função hash e do espalhamento nas chaves
A função de hash poderá, por exemplo, ser implementada pela função modular, considerando a letra inicial do nome convertido para inteiro(ou seja, o código ASCII do caractere em decimal).Em um exemplo onde a Tabela Hash tenha M = 10, para o nome “Maria, a primeira letra “M”, convertido para ASCII decimal o valor é 77, calculando o resto da divisão por 10, a chave será “7”.Contudo, se “maria” fosse escrito em minúsculo, o valor ASCII decimal seria 109, calculando o resto da divisão por 10 a chave seria “9”.Abaixo um exemplo das chaves e seus respectivos
Chav  Nomes iniciados com …
0 F, P, Z, d, n, x
1 G, Q, e, o, y
2 H, R, f, p, z
3 I, S, g, q
4 J, T, h, r
5 A, K, U, i, s
6 B, L, V, j, t
7 C, M, W, a, k, u
8 D, N, X, b, l, v
9 E, O, Y, c, m, w

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lista/lista_encadeada_dupla.c"
#include "../hash/hash.c"
#define M 53

comparastrings(const void* a, const void* b) {
  const char* str_a = *(const char**)a;
  const char* str_b = *(const char**)b;
  return strcmp(str_a, str_b);
}

/*Ordenar os nomes em cada chave individualmente ao inserir*/



/*Abrir arquivo de nomes.txt*/

void abrirArquivo(FILE* arquivo) {
  arquivo = fopen("nomes.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    exit(1);
  }
}

/*Fazer a construção da tabela hash*/

void construirTabelaHash() {
  TabelaHash* tabela = criaTabelaHash(M);
  FILE* arquivo;
  abrirArquivo(arquivo);
  char nome[50];
  while (fscanf(arquivo, "%s", nome) != EOF) {
    insereTabelaHash(tabela, nome);
  }
  imprimeTabelaHash(tabela);
  fclose(arquivo);
}

/*Fazer a inserção dos nomes na tabela hash*/

/*Fazer a busca dos nomes na tabela hash*/

/*Fazer a exportação dos nomes na tabela hash para csv*/

/*Fazer a remoção dos nomes na tabela hash*/