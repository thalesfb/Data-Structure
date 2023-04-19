/* O estacionamento de Scratchemup contém uma única alameda que guarda até dez carros. Os carros entram pela
extremidade sul do estacionamento e saem pela extremidade norte. Se chegar um cliente para retirar um carro que
não esteja estacionado na posição do extremo-norte, todos os carros ao norte do carro serão deslocados para fora,
o carro sairá do estacionamento e os outros carros voltarão à mesma ordem em que se encontravam inicialmente.
Sempre que um carro deixa o estacionamento, todos os carros ao sul são deslocados para frente, de modo que,
o tempo inteiro, todos os espaços vazios estão na parte sul do estacionamento.
Escreva um programa que leia um grupo de linhas de entrada. Cada linha contém um 'C, de chegada, e um 'P', de partida,
 além de um número de placa de licenciamento. Presume-se que os carros chegarão e partirão na ordem especificada
 pela entrada. O programa deve imprimir uma mensagem cada vez que um carro chegar ou partir.
Quando um carro chegar, a mensagem deverá especificar se existe ou não vaga para o carro dentro do estacionamento.
Se não existir vaga, o carro esperará pela vaga ou até que uma linha de partida seja lida para o carro.
Quando houver espaço disponível, outra mensagem deverá ser impressa. Quando um carro partir, a mensagem deverá
incluir o número de vezes que o carro foi deslocado dentro do estacionamento, incluindo a própria partida,
mas não a chegada. Esse número será 0 se o carro for embora a partir da linha de espera.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../filas_tradicionais.c"

int partidaCarro(int, Fila*, Fila*);
void chegadaCarro(int, Fila*, Fila*);
Fila* movimentaCarros(Fila*, int);
void testeEstacionamento(Fila**, Fila**);

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
            scanf(" %c", &entrada);
            printf("Digite a placa do carro:");
            scanf("%d", &placa);
            if (entrada == 'C' || entrada == 'c')
            {
                chegadaCarro(placa, estacionamento, espera);
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
            testeEstacionamento(&estacionamento, &espera);
            opcao = 0;
            break;
        case 4:
            printf("Saindo...");
            liberaFila(estacionamento);
            liberaFila(espera);
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
        printf("Carro com placa %d removido da fila de espera. Número de movimentações %d\n", placa, carro->movimentacao);
    }
    else {
        if (estacionamento->front == carro) {
            removeElementoFila(estacionamento);
            printf("Carro com placa %d removido do estacionamento. Número de movimentações %d\n", placa, carro->movimentacao);
        }
        else {
            estacionamento = movimentaCarros(estacionamento, placa);
            percorreFilaHeadTail(estacionamento);
            while (!filaVazia(espera) && estacionamento->size < 10) {
                Nodo* carroEspera = removeElementoFila(espera);
                if (carroEspera != NULL) {
                    insereElementoFila(estacionamento, carroEspera->dado, carroEspera->movimentacao + 1);
                    printf("Carro com placa %d removido da fila de espera e inserido no estacionamento. Número de movimentações %d\n", carroEspera->dado, carroEspera->movimentacao);
                    liberaMemoriaNodo(carroEspera);
                }
            }
            percorreFilaHeadTail(estacionamento);
            return 1;
        }
    }
    return 0;
}

Fila* movimentaCarros(Fila* estacionamento, int placa) {
    Nodo* primeiro = estacionamento->front;
    Nodo* no = estacionamento->front;
    do
    {
        printf("Primeiro dado: %d\n", primeiro->dado);
        printf("Dado: %d\n", no->dado);
        Nodo* removido = removeElementoFila(estacionamento);
        printf("Removido: %d\n", removido->dado);
        if (no->dado != placa) { //estacionamento->data != placa
            insereElementoFila(estacionamento, removido->dado, removido->movimentacao + 1);
        }
        if (removido->dado != placa) {
            printf("Carro com placa %d movimentado. Número de movimentações: %d\n", estacionamento->rear->dado, estacionamento->rear->movimentacao);
        }
        no = no->next;
    } while (no->dado != primeiro->dado);
    return estacionamento;
}

void chegadaCarro(int placa, Fila* estacionamento, Fila* espera) {
    if (estacionamento->size < 10) {
        insereElementoFila(estacionamento, placa, 0);//movimento +1
        printf("Carro com placa %d inserido no estacionamento.\n", placa);//movimento +1
    }
    else {
        insereElementoFila(espera, placa, 0);
        printf("Carro com placa %d inserido na fila de espera.\n", placa);
    }
}

void testeEstacionamento(Fila** estacionamento, Fila** espera) {
    chegadaCarro(1, *estacionamento, *espera);
    chegadaCarro(2, *estacionamento, *espera);
    chegadaCarro(3, *estacionamento, *espera);
    chegadaCarro(4, *estacionamento, *espera);
    chegadaCarro(5, *estacionamento, *espera);
    chegadaCarro(6, *estacionamento, *espera);
    chegadaCarro(7, *estacionamento, *espera);
    chegadaCarro(8, *estacionamento, *espera);
    chegadaCarro(9, *estacionamento, *espera);
    chegadaCarro(10, *estacionamento, *espera);
    chegadaCarro(11, *estacionamento, *espera);
    chegadaCarro(12, *estacionamento, *espera);

    partidaCarro(3, *estacionamento, *espera);
    partidaCarro(10, *estacionamento, *espera);
    partidaCarro(12, *estacionamento, *espera);
    partidaCarro(1, *estacionamento, *espera);
}
