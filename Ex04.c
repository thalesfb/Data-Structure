#include <stdio.h>
#include <stdlib.h>

void soma(int mat1 [3][3], int mat2 [3][3]){
    int mat3[3][3];
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mat3[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    for (i = 0; i < 3; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            printf("%d   ", mat3[i][j]);

        }
        printf("\n\n");
    }
}
int main(int argc, char** argv) {

    int mat1 [3][3],mat2 [3][3];
    int i;
    int j;
    printf("Digite os elementos da primeira matriz 3x3\n\n");
    for (i = 0; i < 3; i++) {
        
        for (j = 0; j < 3; j++) {
            printf("\nElemento [%d][%d]:", i, j);
            scanf("%d", &mat1[i][j]);
        }
    }
    printf("\n\nDigite os elementos da segunda matriz 3x3\n\n");
    for (i = 0; i < 3; i++) {
        
        for (j = 0; j < 3; j++) {
            printf("\nElemento [%d][%d]:", i, j);
            scanf("%d", &mat2[i][j]);
        }
    }
    printf("\n\nA primeira matriz eh\n\n");
    for (i = 0; i < 3; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            printf("%d   ", (mat1[i][j]));

        }
        printf("\n\n");
    }
    printf("\n\nA segunda matriz eh\n\n");
    for (i = 0; i < 3; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            printf("%d   ", (mat2[i][j]));
        }
        printf("\n\n");
    }
    printf("\n\nA soma des matrizes eh\n\n");
        soma(mat1,mat2);


    return (EXIT_SUCCESS);
}

