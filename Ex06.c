#include <stdio.h>
#include <stdlib.h>
int m, n;

void calculaMagico(int matriz[m][n]) {
    int i, j, lin[m], col[n], cont = 0, diag[2], aux = 0;
    diag[0] = 0;
    diag[1] = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            cont += matriz[i][j];
            if (i == j) diag[0] += matriz[i][j];
        }
        lin[i] = cont;
        cont = 0;
    }
    cont = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cont += matriz[j][i];
        }
        col[i] = cont;
        cont = 0;
    }
    cont = 0;
    for (i = (m - 1); i >= 0; i--) {
            diag[1] += matriz[i][cont];
            cont++;
    }
    if (((lin[aux] == lin[aux + 1]) && (lin[aux] == lin[aux + 2]))) {
        if (((col[aux] == col[aux + 1]) && (col[aux] == col[aux + 2]))) {
            if (diag[aux] == diag[aux + 1]) {
                printf("\n\nA matriz eh um quadrado magico!!\n");
            }
        }
    }
}

int main(int argc, char** argv) {

    do {
        printf("Digite o tamano da sua matriz(m = linha e n= coluna) no formato m,n: ");
        scanf("%d, %d", &m, &n);
        if (n != m) {
            printf("\nA matriz tem que ser quadrada!\n\n");
        }
    } while (n != m);
    int mat [m][n];
    int i, j;
    printf("Digite os elementos de matriz %dx%d\n\n", m, n);
    for (i = 0; i < m; i++) {

        for (j = 0; j < n; j++) {
            printf("\nElemento [%d][%d]:", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
    system("cls");
    printf("\n\nA matriz ficou\n\n");
    for (i = 0; i < m; i++) {
        printf("  ");
        for (j = 0; j < n; j++) {
            printf("%d   ", mat[i][j]);
        }
        printf("\n\n");
    }
    calculaMagico(mat);
    return (EXIT_SUCCESS);
}