#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <inttypes.h>
#include "../filas_tradicionais.h"


//protótipos
int partidaCarro(int, Fila*, Fila*);
void chegadaCarro(int, Fila*, Fila*);
Fila* movimentaCarros(Fila*, int);

int main() {

    int opcao = 0, placa = 0;
    char entrada;
    Fila* estacionamento = criaFila();
    Fila* espera = criaFila();

    while (opcao != 3)
    {
        printf("\n\n");
        printf("Digite uma das opções abaixo:\n");
        printf("1 - Movimentação\n");
        printf("2 - Ver estacionamento\n");
        printf("3 - Testar o estacionamento\n");
        printf("4 - Sair\n");
        printf("Opção: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite a movimentação(C para chegada e P pra Partida): ");
            //fflush(stdin);
            scanf(" %c", &entrada);
            printf("Digite a placa do carro:");
            scanf("%d", &placa);
            if (entrada == 'C' || entrada == 'c')
            {
                if (estacionamento->size == 10)
                {
                    printf("Estacionamento cheio! Ficará no aguardo de uma vaga!");
                    insereElementoFila(espera, placa);
                }
                else
                {
                    insereElementoFila(estacionamento, placa);
                }
            }
            else if (entrada == 'P' || entrada == 'p')
            {
                if (partidaCarro(placa, estacionamento, espera) == 0)
                {
                    printf("Carro não encontrado!");
                }
            }
            else
            {
                printf("Entrada inválida!");
            }
            opcao = 0;
            break;
        case 2:
            printf("Estacionamento: ");
            percorreFilaHeadTail(estacionamento);
            printf("\n");
            printf("Fila de espera: ");
            percorreFilaHeadTail(espera);
            printf("\n");
            opcao = 0;
            break;
        case 3:
            testeFila();
            opcao = 0;
            break;
        case 4:
            printf("Saindo...");
            exit(0);
            break;
        default:
            printf("Opção inválida!");
            opcao = 0;
            break;
        }
    }
    return 0;
}

//implementação


int partidaCarro(int placa, Fila* estacionamento, Fila* espera) {

    Nodo* carro = buscaFila(estacionamento, placa);

    if (carro == NULL) {
        liberaMemoriaNodo(carro);
        Nodo* carro = buscaFila(espera, placa);
        if (carro == NULL) {
            printf("Carro com placa %d não encontrado.\n", placa);
            return 1;
        }
        removeElementoFila(espera);
        printf("Carro com placa %d removido da fila de espera.\n", placa);
    }
    else {
        Nodo* removido = removeElementoFila(estacionamento);
        printf("Carro com placa %d removido do estacionamento. Número de movimentações: %d\n", removido->dado);//movimento +1
        estacionamento = movimentaCarros(estacionamento, placa);
        liberaMemoriaNodo(removido);
        while (!filaVazia(espera) && estacionamento->size < 10) {
            Nodo* carroEspera = removeElementoFila(espera);
            if (carroEspera != NULL) {
                insereElementoFila(estacionamento, carroEspera->dado);//movimento +1
                printf("Carro com placa %d removido da fila de espera e inserido no estacionamento. Número de movimentações: %d\n", carroEspera->dado);//movimento +1
                liberaMemoriaNodo(carroEspera);
            }
        }
    }
    return 0;
}

Fila* movimentaCarros(Fila* estacionamento, int placa) {
    Nodo* primeiro = estacionamento->front;
    Nodo* no = estacionamento->front;

    if (primeiro->dado != placa) {
        while (no->next != primeiro)
        {
            Nodo* removido = removeElementoFila(estacionamento);
            if (removido->dado != placa) {
                insereElementoFila(estacionamento, removido->dado); //movimento +1
                //printf("Carro com placa %d movimentado. Número de movimentações: %d\n", removido->placa, removido->movimentacao);
                liberaMemoriaNodo(removido);
            }
            no = no->next;
        }
    }
    return estacionamento;
}