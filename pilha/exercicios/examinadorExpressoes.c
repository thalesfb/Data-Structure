/* Uma utilização prática de pilhas poderia ser para solucionar o problema de examinar expressões
matemáticas que contém vários conjuntos de parênteses agrupados. Exemplo:
7 – ((x * ((x + y) / (j – 3)) + y) / (4 – 2.5))

É necessário garantir que os parênteses estejam corretamente agrupados, ou seja,
deseja-se verificar que:
Existe um número igual de parênteses esquerdos e direitos?
Todo parênteses da direita está precedido por um parênteses da esquerda correspondente?

Assim, expressões como: “((a + b) ou a + b(“, violam o critério 1, e
expressões como: “)a + b(-c ou (a + b)) – (c + d”, violam o critério 2.

Para solucionar esse problema, pode-se imaginar cada parênteses da esquerda como uma
abertura de um escopo, e cada parênteses da direita como um fechamento de escopo.
A profundidade do agrupamento em determinado ponto numa expressão é o número de escopos abertos,
mas ainda não fechados nesse ponto. Isto corresponderá ao número de parênteses da
esquerda encontrados cujos correspondentes parênteses da direita ainda não foram encontrados.
Determina-se a contagem de parênteses em determinado ponto numa expressão como o número de
parênteses da esquerda menos o número de parênteses da direita encontrado ao rastrear a
expressão a partir do início até o ponto em questão. Se a contagem de parênteses for não-negativa,
 ela equivalerá a profundidade de aninhamento. As duas condições que devem vigorar
 caso os parênteses de uma expressão formem um padrão admissível são:
A contagem de parênteses no final da expressão é 0. Isso implica que nenhum escopo ficou
aberto ou que foi encontrada a mesma quantidade de parênteses da direita e da esquerda.
A contagem de parênteses em cada ponto da expressão é não-negativa. Isso implica que não
foi encontrado um parênteses da direita para o qual não exista um correspondente parênteses da esquerda.

Alterando ligeiramente o problema e supondo a existência de três tipos diferentes de
delimitadores de escopo. Esses tipos são indicados por parênteses (e), colchetes [e] e chaves {e}.
Um finalizador de escopo deve ser do mesmo tipo de seu iniciador. Sendo assim,
expressões como ( a + b], [(a + b]), {a – (b]}, são inválidas.
É necessário rastrear não somente quantos escopos foram abertos como também seus tipos.
Estas informações são importantes porque, quando um finalizador de escopo é encontrado,
 precisa-se conhecer o símbolo com o qual o escopo foi aberto para assegurar que ele seja
 corretamente fechado.

Uma pilha pode ser usada para rastrear os tipos de escopos encontrados.
Sempre que um iniciador de escopo for encontrado, ele será empilhado.
Sempre que um finalizador de escopo for encontrado, a pilha será examinada.
Se a pilha estiver vazia, o finalizador de escopo não terá um iniciador correspondente e
a string será, consequentemente, inválida. Entretanto se a pilha não estiver vazia,
desempilha e verifica se o item desempilhado corresponde ao finalizador de escopo.
Se ocorrer uma coincidência, o processo continua, caso contrária, a expressão é inválida.
Quando o final da expressão for encontrada, a pilha deverá estar vazia. Caso contrário,
existem um ou mais escopos abertos que ainda não foram fechados, e a expressão será inválida.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../pilha.c"
#include <locale.h>

#define n 100

typedef struct sTeste {
  const char* expressao;
  bool valido;
} Teste;

Teste testes[] = {
  {"(A + B}", false},
  {"{[A + B] - [(C - D)]", false},
  {"(A + B)-{C + D}-[F+ G]", true},
  {"((H) * {([J + K])})", true},
  {"(((A))))", false},
};

bool delimitadorAbre(char);
bool delimitadorFecha(char);
bool delimitadorCorreto(char, char);
bool validaExpressao(char*);

int main() {

  setlocale(LC_ALL, "pt_BR.UTF-8");

  char expressao[n];
  int opcao = 0;

  while (opcao != 3)
  {
    printf("\n\n");
    printf("1 - Testar expressoes\n");
    printf("2 - Inserir expressao\n");
    printf("3 - Sair\n");
    printf("Opcao: ");
    fflush(stdin);
    scanf("%d", &opcao);
    getchar();
    switch (opcao)
    {
    case 1:
      for (size_t i = 0; i < strlen(expressao); i++)
      {
        printf("\n");
        printf("Expressao: %s", testes[i].expressao);
        if (validaExpressao((char*)testes[i].expressao))
        {
          printf(" eh valida! ");
        }
        else {
          printf(" eh invalida! ");
        }
        printf("Esperado: %s", testes[i].valido ? "Valido" : "Invalido");
      }
      opcao = 0;
      break;
    case 2:
      printf("Digite uma expressao: ");
      fgets(expressao, n, stdin);
      expressao[strcspn(expressao, "\n")] = '\0';
      expressao[strlen(expressao)] = '\0';
      if (validaExpressao(expressao))
      {
        printf(" é valida!");
      }
      else {
        printf(" é invalida!");
      }
      opcao = 0;
      break;
    case 3:
      printf("Saindo...");
      //liberaPilha(pilha);
      break;
    default:
      printf("Opção invalida!");
      opcao = 0;
      break;
    }
  }
}

bool delimitadorAbre(char c) {
  return c == '(' || c == '[' || c == '{';
}

bool delimitadorFecha(char c) {
  return c == ')' || c == ']' || c == '}';
}

bool delimitadorCorreto(char c1, char c2) {
  return (c2 == ')' && c1 == '(') || (c2 == ']' && c1 == '[') || (c2 == '}' && c1 == '{');
}

bool validaExpressao(char* expressao)
{
  Lista* pilha = criaLista();
  if (pilha == NULL)
  {
    printf("Erro ao criar pilha\n");
    return false;
  }
  for (size_t i = 0; i < strlen(expressao); i++)
  {
    printf("\n");
    percorrePilha(pilha);
    char c = expressao[i];
    printf("Caractere: %c\n", c);
    if (delimitadorAbre(c))
    {
      printf("Empilhando delimitador: %c\n", c);
      push(pilha, criaNodo((int)c));
    }
    else if (delimitadorFecha(c))
    {
      printf("Encontrado delimitador de fechamento: %c\n", c);
      if (pilhaVazia(pilha))
      {
        printf("Pilha vazia. Delimitador sem correspondencia\n");
        liberaPilha(pilha);
        return false;
      }
      else {
        if (delimitadorCorreto((char)pilha->tail->dado, c))
        {
          printf("Delimitadores correspondem: %c e %c\n", (char)pilha->tail->dado, c);
          Nodo* nodo = pop(pilha);
          char c2 = (char)nodo->dado;
          if (nodo == NULL)
          {
            printf("Erro ao desempilhar\n");
            liberaPilha(pilha);
            return false;
          }
          else if (c2 == '\0')
          {
            printf("Erro ao desempilhar\n");
            free(nodo);
            liberaPilha(pilha);
            return false;
          }
          free(nodo);
          printf("Desempilhando delimitador: %c\n", c2);
        }
        else {
          printf("Delimitadores nao correspondem: %c e %c\n", (char)pilha->tail->dado, c);
          liberaPilha(pilha);
          return false;
        }
      }
    }
  }
  if (pilhaVazia(pilha))
  {
    printf("Pilha vazia, expressao valida!\n");
    liberaPilha(pilha);
    return true;
  }
  else {
    printf("Pilha nao vazia, expressao invalida!\n");
    liberaPilha(pilha);
    return false;
  }
}