#include <assert.h>
#include "../lista/lista_encadeada_dupla.c"	

//protótipos
void testCriaLista();
void testInsereElementoLista(Lista*);
void testBuscaLista(Lista*);
void testRemoveElementoLista(Lista*);
void testLiberaMemoriaLista(Lista*);

//implementações
void testCriaLista() {
  Lista* lista = criaLista();
  assert(lista != NULL);
  assert(lista->size == 0);
  printf("Teste criaLista passou.\n");
}

void testInsereElementoLista(Lista* lista) {
  assert(insereElementoLista(lista, lista->tail, "João") == 0);
  assert(insereElementoLista(lista, lista->tail, "Maria") == 0);
  assert(lista->size == 2);
  printf("Teste insereElementoLista passou.\n");
}

void testBuscaLista(Lista* lista) {
  assert(buscaLista(lista, "João") != NULL);
  assert(buscaLista(lista, "Maria") != NULL);
  assert(buscaLista(lista, "Ana") == NULL);
  printf("Teste buscaLista passou.\n");
}

void testRemoveElementoLista(Lista* lista) {
  Nodo* no = buscaLista(lista, "João");
  assert(no != NULL);
  removeElementoLista(lista, no);
  assert(buscaLista(lista, "João") == NULL);
  assert(lista->size == 1);
  printf("Teste removeElementoLista passou.\n");
}

void testLiberaMemoriaLista(Lista* lista) {
  liberaMemoriaLista(lista);
  printf("Teste liberaMemoriaLista passou.\n");
}

int main() {
  Lista* lista = criaLista();
  testCriaLista();
  testInsereElementoLista(lista);
  testBuscaLista(lista);
  testRemoveElementoLista(lista);
  testLiberaMemoriaLista(lista);
  printf("Todos os testes passaram.\n");
  return 0;
}
