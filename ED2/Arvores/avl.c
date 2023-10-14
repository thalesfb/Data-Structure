#include <stdio.h>
#include <stdlib.h>

//criação de uma árvore binária balanceada

//estrutura de um nó de uma árvore binária balanceada
typedef struct sNo
{
  int chave;
  struct sNo* esq, * dir;
  int altura;
} No;

//estrutura de uma árvore binária balanceada
typedef struct
{
  No* raiz;
} AVL;

//protótipos
No* alocaMemoriaNo();
AVL* alocaMemoriaAVL();
void liberaNo(No*);
void liberaArvore(AVL*);
No* criaNo(int);
AVL* criaArvoreAVL();
int maiorValor(int, int);
No* insere(No*, int);
No* insereArvore(AVL*, int);
No* balancear(No*);
No* busca(No*, int);
No* removeNo(No*, int);
void remover(AVL*, int);
No* menorValorSubArvoreDireita(No*);
No* maiorValorSubArvoreEsquerda(No*);
No* RR(No*);
No* LL(No*);
No* RL(No*);
No* LR(No*);
int fatorBalanceamento(No*);
int altura(No*);
void imprime(AVL*);
void emOrdem(No*);
void preOrdem(No*);
void posOrdem(No*);
void menu();

//função que aloca memória para um nó de uma árvore binária balanceada
No* alocaMemoriaNo()
{
  No* novo = (No*)malloc(sizeof(No));
  if (novo == NULL)
  {
    printf("Erro ao alocar memória para o nó!\n");
    exit(1);
  }
  printf("Nó alocado!\n");
  return novo;
}

//função que aloca memória para uma árvore binária balanceada
AVL* alocaMemoriaAVL() {
  AVL* novo = (AVL*)malloc(sizeof(AVL));
  if (novo == NULL) {
    printf("Erro ao alocar memoria para a arvore!\n");
    exit(1);
  }
  printf("Árvore alocada!\n");
  return novo;
}

//função que libera memória de um nó de uma árvore binária balanceada
void liberaNo(No* no)
{
  if (no != NULL)
  {
    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no);
    printf("Nó liberado!\n");
  }
}

//função que libera memória de uma árvore binária balanceada
void liberaArvore(AVL* arvore)
{
  if (arvore != NULL)
  {
    liberaNo(arvore->raiz);
    free(arvore);
    printf("Árvore liberada!\n");
  }
}

//função que cria um nó de uma árvore binária balanceada
No* criaNo(int chave)
{
  No* novo = alocaMemoriaNo();
  if (novo == NULL)
  {
    printf("Erro ao alocar memória para o nó!\n");
    exit(1);
  }
  novo->chave = chave;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->altura = 0;
  printf("Nó criado!\n");
  return novo;
}

//função que cria uma árvore binária balanceada
AVL* criaArvoreAVL()
{
  AVL* novo = alocaMemoriaAVL();
  if (novo == NULL)
  {
    printf("Erro ao alocar memória para a árvore!\n");
    exit(1);
  }
  novo->raiz = NULL;
  printf("Árvore criada!\n");
  return novo;
}

//função que retorna o maior altura entre dois nós
int maiorValor(int a, int b)
{
  return (a > b) ? a : b;
}

//função que insere um nó em uma árvore binária balanceada
No* insere(No* no, int chave)
{
  printf("Inserindo nó com chave: %d\n", chave);
  if (no == NULL)
  {
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
  printf("Verificando altura...\n");
  no->altura = maiorValor(altura(no->esq), altura(no->dir)) + 1;
  printf("Altura: %d\n", no->altura);
  printf("Verificando balanceamento...\n");
  no = balancear(no);

  return no;
}

//função que insere um nó em uma árvore binária balanceada
No* insereArvore(AVL* arvore, int chave)
{
  if (arvore == NULL)
  {
    printf("Árvore não existe!\n");
    return NULL;
  }
  printf("Inserindo nó na árvore\n");
  return arvore->raiz = insere(arvore->raiz, chave);
}

//função que balanceia uma árvore binária balanceada
No* balancear(No* no)
{
  int fator = fatorBalanceamento(no);
  if (fator > 1)
  {
    printf("Fator de balanceamento: %d\n", fator);
    if (fatorBalanceamento(no->esq) > 0)
    {
      printf("Rotação RR\n");
      no = RR(no);
    }
    else
    {
      printf("Rotação RL\n");
      no = RL(no);
    }
  }
  else if (fator < -1)
  {
    printf("Fator de balanceamento: %d\n", fator);
    if (fatorBalanceamento(no->dir) < 0)
    {
      printf("Rotação LL\n");
      no = LL(no);
    }
    else
    {
      printf("Rotação LR\n");
      no = LR(no);
    }
  }
  return no;
}

//função que busca um nó em uma árvore binária balanceada
No* busca(No* raiz, int chave)
{
  if (raiz == NULL)
  {
    printf("Nó não encontrado!\n");
    return NULL;
  }
  if (raiz->chave == chave)
  {
    printf("Nó encontrado!\n");
    return raiz;
  }
  if (chave < raiz->chave)
  {
    raiz->esq = busca(raiz->esq, chave);
  }
  else if (chave > raiz->chave)
  {
    raiz->dir = busca(raiz->dir, chave);
  }
}

//função que remove um nó de uma árvore binária balanceada
No* removeNo(No* no, int chave)
{
  if (no == NULL)
  {
    printf("Nó não existe!\n");
    return NULL;
  }
  if (chave < no->chave)
  {
    no->esq = removeNo(no->esq, chave);
  }
  else if (chave > no->chave)
  {
    no->dir = removeNo(no->dir, chave);
  }
  else
  {
    if (no->esq == NULL)
    {
      No* aux = no->dir;
      free(no);
      //verificar se a árvore ficou desbalanceada

      return aux;
    }
    else if (no->dir == NULL)
    {
      No* aux = no->esq;
      free(no);
      //verificar se a árvore ficou desbalanceada
      return aux;
    }
    No* aux = menorValorSubArvoreDireita(no->dir);
    no->chave = aux->chave;
    no->dir = removeNo(no->dir, aux->chave);
  }
  return no;
}

//função que remove um nó de uma árvore binária balanceada
void remover(AVL* arvore, int chave)
{
  if (arvore == NULL)
  {
    printf("Árvore não existe!\n");
    return;
  }
  arvore->raiz = removeNo(arvore->raiz, chave);
  printf("Nó removido!\n");

  //verificar se a árvore ficou desbalanceada
  arvore->raiz = balancear(arvore->raiz);
}

//função que retorna o menor valor de uma subárvore direita
No* menorValorSubArvoreDireita(No* no)
{
  No* aux = no;
  while (aux->esq != NULL)
  {
    aux = aux->esq;
  }
  return aux;
}

//função que retorna o maior valor de uma subárvore esquerda
No* maiorValorSubArvoreEsquerda(No* no)
{
  No* aux = no;
  while (aux->dir != NULL)
  {
    aux = aux->dir;
  }
  return aux;
}

//função que realiza a rotação simples à direita
No* RR(No* no)
{
  No* aux = no->esq;
  no->esq = aux->dir;
  aux->dir = no;
  no->altura = maiorValor(altura(no->esq), altura(no->dir)) + 1;
  aux->altura = maiorValor(altura(aux->esq), altura(aux->dir)) + 1;
  return aux;
}

//função que realiza a rotação simples à esquerda
No* LL(No* no)
{
  No* aux = no->dir;
  no->dir = aux->esq;
  aux->esq = no;
  no->altura = maiorValor(altura(no->esq), altura(no->dir)) + 1;
  aux->altura = maiorValor(altura(aux->esq), altura(aux->dir)) + 1;
  return aux;
}

//função que realiza a rotação dupla à direita
No* RL(No* no)
{
  no->esq = RR(no->esq);
  return LL(no);
}

//função que realiza a rotação dupla à esquerda
No* LR(No* no)
{
  no->dir = LL(no->dir);
  return RR(no);
}

//função que retorna o fator de balanceamento de um nó
int fatorBalanceamento(No* no)
{
  if (no == NULL)
    return -1;
  else {
    printf("Altura esquerda: %d\n", altura(no->esq));
    printf("Altura direita: %d\n", altura(no->dir));
    return altura(no->esq) - altura(no->dir);
  }
}

//função que retorna a altura de um nó
/* int altura(No* no)
{
  if (no == NULL)
    return 0;
  int altura_esq = altura(no->esq);
  int altura_dir = altura(no->dir);
  if (altura_esq > altura_dir)
    return altura_esq + 1;
  return altura_dir + 1;
} */

int altura(No* no)
{
  if (no == NULL)
    return -1;
  printf("Altura: %d\n", no->altura);
  return no->altura;
}

//função que imprime uma árvore binária balanceada
void imprime(AVL* arvore)
{
  if (arvore == NULL)
  {
    printf("Árvore não existe!\n");
    return;
  }
  printf("Imprimindo em ordem:\n");
  emOrdem(arvore->raiz);
  printf("\nImprimindo em pré-ordem:\n");
  preOrdem(arvore->raiz);
  printf("\nImprimindo em pós-ordem:\n");
  posOrdem(arvore->raiz);
  printf("\n");
}

//função que imprime uma árvore binária balanceada em ordem
void emOrdem(No* raiz)
{
  if (raiz != NULL)
  {
    emOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    emOrdem(raiz->dir);
  }
}

//função que imprime uma árvore binária balanceada em pré-ordem
void preOrdem(No* raiz)
{
  if (raiz != NULL)
  {
    printf("%d ", raiz->chave);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}

//função que imprime uma árvore binária balanceada em pós-ordem
void posOrdem(No* raiz)
{
  if (raiz != NULL)
  {
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf("%d ", raiz->chave);
  }
}

//função que imprime o menu
void menu()
{
  printf("0 - Sair\n");
  printf("1 - Criar\n");
  printf("2 - Inserir\n");
  printf("3 - Buscar\n");
  printf("4 - Remover\n");
  printf("5 - Imprimir\n");
  printf("6 - Testar\n");
}

void testArvore() {

  /*   Insira em uma árvore AVL os itens com as chaves apresentadas a seguir(na ordem em que aparecem).Desenhe a árvore resultante da inserção, sendo que uma nova árvore deve ser desenhada quando houver alguma rotação.Indique qual a rotação que foi executada :

    30, 40, 24, 58, 48, 26, 11, 13, 14
    20, 15, 25, 10, 30, 24, 17, 12, 5, 3
    40, 30, 50, 45, 55, 52
    20, 15, 25, 12, 17, 24, 30, 10, 14, 13
    20, 15, 25, 12, 17, 30, 26 */

  AVL* arvore = criaArvoreAVL();

  insereArvore(arvore, 30);
  insereArvore(arvore, 40);
  insereArvore(arvore, 24);
  insereArvore(arvore, 58);
  insereArvore(arvore, 48);
  insereArvore(arvore, 26);
  insereArvore(arvore, 11);
  insereArvore(arvore, 13);
  insereArvore(arvore, 14);

  imprime(arvore);
  liberaArvore(arvore);

  /*   AVL* arvore = criaArvoreAVL();

    insereArvore(arvore, 20);
    insereArvore(arvore, 15);
    insereArvore(arvore, 25);
    insereArvore(arvore, 10);
    insereArvore(arvore, 30);
    insereArvore(arvore, 24);
    insereArvore(arvore, 17);
    insereArvore(arvore, 12);
    insereArvore(arvore, 5);
    insereArvore(arvore, 3);

    imprime(arvore);
    liberaArvore(arvore);

    AVL* arvore = criaArvoreAVL();

    insereArvore(arvore, 40);
    insereArvore(arvore, 30);
    insereArvore(arvore, 50);
    insereArvore(arvore, 45);
    insereArvore(arvore, 55);
    insereArvore(arvore, 52);

    imprime(arvore);
    liberaArvore(arvore);

    AVL* arvore = criaArvoreAVL();

    insereArvore(arvore, 20);
    insereArvore(arvore, 15);
    insereArvore(arvore, 25);
    insereArvore(arvore, 12);
    insereArvore(arvore, 17);
    insereArvore(arvore, 24);
    insereArvore(arvore, 30);
    insereArvore(arvore, 10);
    insereArvore(arvore, 14);
    insereArvore(arvore, 13);

    imprime(arvore);
    liberaArvore(arvore);

    AVL* arvore = criaArvoreAVL();

    insereArvore(arvore, 20);
    insereArvore(arvore, 15);
    insereArvore(arvore, 25);
    insereArvore(arvore, 12);
    insereArvore(arvore, 17);
    insereArvore(arvore, 30);
    insereArvore(arvore, 26);

    imprime(arvore);
    liberaArvore(arvore); */
}
int main() {

  testArvore();
  /*  int opcao, chave;


    do {
      menu();
      printf("O que deseja fazer?\n");
      printf("> ");
      scanf("%d", &opcao);
      switch (opcao) {
      case 0:
        printf("Saindo...\n");
        break;
      case 1:
        //AVL* arvore = criaArvoreAVL();
        break;
      case 2:
        printf("Digite a chave a ser inserida: ");
        scanf("%d", &chave);
        if (arvore == NULL)
        {
          printf("Arvore nao criada!\n");
          break;
        }
        insereArvore(arvore, chave);
        break;
      case 3:
        printf("Digite a chave a ser removida: ");
        scanf("%d", &chave);
        if (arvore == NULL)
        {
          printf("Arvore nao criada!\n");
          break;
        }
        remover(arvore, chave);
        break;
      case 4:
        printf("Digite a chave a ser buscada: ");
        scanf("%d", &chave);
        if (arvore == NULL)
        {
          printf("Arvore nao criada!\n");
          break;
        }
        busca(arvore->raiz, chave);
        break;
      case 5:
        if (arvore == NULL)
        {
          printf("Arvore nao criada!\n");
          break;
        }
        imprime(arvore);
        break;
      case 6:
        testArvore();
        break;
      default:
        printf("Opcao invalida!\n");
        break;
      }
    } while (opcao != 0); */
  return 0;
}