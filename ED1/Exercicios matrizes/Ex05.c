#include <stdio.h>
#include <stdlib.h>
int m, n;

void calculaNulo(int matriz[m][n]) {
    int i, j, lin=0, col=0, cont=0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if(matriz[i][j] == 0) cont++;
        }
        if (cont == n) lin++;
    }
    cont =0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if(matriz[i][j] == 0) cont++;
        }
        if (cont == m) col++;
    }
    printf("\nLinhas nulas: %d\nColunas nulas: %d\n\n", lin, col);
}

int main(int argc, char** argv) {

    printf("Digite o tamano da sua matriz(m = linha e n= coluna) no formato m,n: ");
    scanf("%d, %d", &m, &n);
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
    calculaNulo(mat);

    return (EXIT_SUCCESS);
}

