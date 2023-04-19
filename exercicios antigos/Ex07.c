/*OBS: nao consegui representa a matriz tridimensional entao coloquei de que posicao ela saiu*/

#include <stdio.h>
#include <stdlib.h>

void soma(int mat1 [3][3][3], int mat2 [3][3][3]) {
    int mat3[3][3][3];
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                mat3[i][j][k] = mat1[i][j][k] + mat2[i][j][k];
            }
        }
    }
    for (i = 0; i < 3; i++) {
        //printf("  ");
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                printf("Elemento[%d][%d][%d] = %d   \n", i,j,k,mat3[i][j][k]);
            }
        }
    }
}

int main(int argc, char** argv) {

    int mat1 [3][3][3], mat2 [3][3][3];
    int i, j, k;
    printf("Digite os elementos da primeira matriz 3x3x3\n\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                printf("\nElemento [%d][%d][%d]:", i, j, k);
                scanf("%d", &mat1[i][j][k]);
            }
        }
    }
    printf("\n\nDigite os elementos da segunda matriz 3x3\n\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                printf("\nElemento [%d][%d][%d]:", i, j, k);
                scanf("%d", &mat2[i][j][k]);
            }
        }
    }
    printf("\n\nA primeira matriz eh\n\n");
    for (i = 0; i < 3; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                printf("Elemento[%d][%d][%d] = %d   \n", i,j,k,mat1[i][j][k]);
            }
        }
        printf("\n\n");
    }
    printf("\n\nA segunda matriz eh\n\n");
    for (i = 0; i < 3; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                printf("Elemento[%d][%d][%d] = %d   \n", i,j,k,mat2[i][j][k]);
            }
        }
        printf("\n\n");
    }
    printf("\n\nA soma des matrizes eh\n\n");
    soma(mat1, mat2);


    return (EXIT_SUCCESS);
}

