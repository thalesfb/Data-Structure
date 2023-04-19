#include <stdio.h>
#include <stdlib.h>

int validacao(char matriz[3][3]) { //verificacao se ha vencedor
    int i, j;
    int cont = 0;
    int vit = 0;
    for (i = 0; i < 3; i++) {

        if (((matriz[i][cont] == matriz [i][cont + 1])) && (matriz[i][cont] == matriz [i][cont + 2])) {
            if ((matriz[i][cont]) != '\0') {
                vit = 1;
            }
        }
    }
    for (j = 0; j < 3; j++) {

        if (((matriz[cont][j] == matriz [cont + 1][j])) && (matriz[cont][j] == matriz [cont + 2][j])) {
            if ((matriz[cont][j]) != '\0') {
                vit = 1;
            }
        }
    }
    if (((matriz[cont][cont] == matriz [cont + 1][cont + 1])) && (matriz[cont][cont] == matriz [cont + 2][cont + 2])) {
        if ((matriz[cont][cont]) != '\0') {
            vit = 1;
        }
    }
    if (((matriz[cont + 2][cont] == matriz [cont + 1][cont + 1])) && (matriz[cont + 2][cont] == matriz [cont][cont + 2])) {
        if ((matriz[cont + 2][cont]) != '\0') {
            vit = 1;
        }
    }

    return vit; //verificacao se ha vencedor
}

int main(int argc, char** argv) {

    char mat [3][3];
    int tmp1, tmp2, aux, aux2 = 0;
    int i;
    int j;
    char elem;
    int valida = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mat[i][j] = '\0';
        }
    }
    printf("\n\t\t\tJogo da velha\n\n\n");
    do {
        printf("Em que linha deseja inserir o dado? (0 a 2 ou -1 para sair): ");
        scanf("%d", &aux);
        if (aux >= 0 && aux <= 2) {
            tmp1 = aux;
        } else if (aux == -1) return 0;
        printf("Em que coluna deseja inserir o dado? (0 a 2 ou -1 para sair): ");
        scanf("%d", &aux);
        if (aux >= 0 && aux <= 2) {
            tmp2 = aux;
        } else if (aux == -1) return 0;
        fflush(stdin);
        while ((mat[tmp1][tmp2]) != '\0') {
            printf("Opa, esta casa ja esta ocupada! Digite outra posicao.\n");
            printf("Em que linha deseja inserir o dado? (0 a 2 ou -1 para sair): ");
            scanf("%d", &aux);
            if (aux >= 0 && aux <= 2) {
                tmp1 = aux;
            } else if (aux == -1) return 0;
            printf("Em que coluna deseja inserir o dado? (0 a 2 ou -1 para sair): ");
            scanf("%d", &aux);
            if (aux >= 0 && aux <= 2) {
                tmp2 = aux;
            } else if (aux == -1) return 0;
            fflush(stdin);
        }
        if ((mat[tmp1][tmp2]) == '\0') {
volta:
            printf("Digite o elemento que deseja inserir(X ou O): ");
            scanf("%c", &elem);
            fflush(stdin);
            if (((elem == 88) || (elem == 120)) || ((elem == 79) || (elem == 111))) {
                mat[tmp1][tmp2] = elem;
            } else {
                printf("Digito nao suportado. Digite novamente.\n");
                goto volta;
            }
        }
        system("cls");
        printf("O jogo esta assim: \n");
        for (i = 0; i < 3; i++) {
            printf("  ");
            for (j = 0; j < 3; j++) {
                printf("%c   ", (mat[i][j]));
            }
            printf("\n\n");
        }
        valida = validacao(mat);
        int k; //verificacao se deu velha
        for (k = 0; k < 3; k++) {
            int h;
            for (h = 0; h < 3; h++) {
                if ((mat[k][h]) != '\0') aux2++;
            }
        }
        if (aux2 == 9) {
            printf("\n\n\n\t\t\tDeu velha! :s\n\n");
            return 0;
        }
        aux2 = 0; //verificacao se deu velha
        if (valida == 1) {
            printf("O jogo acabou, ouve um vencedor.\n");
        }
    } while (valida == 0);


    return (EXIT_SUCCESS);
}