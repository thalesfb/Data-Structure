#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int mat [3][3];
    int vet [3];
    int i;
    int j;
    printf("Digite os elementos de matriz 3x3\n\n");
    for (i = 0; i < 3; i++) {
        
        for (j = 0; j < 3; j++) {
            printf("\nElemento [%d][%d]:", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
    printf("\n\nDigite os 3 elementos do vetor\n\n");
        for (i = 0; i < 3; i++) {
            printf("\nElemento [%d]:", i);
            scanf("%d", &vet[i]);
        }
        printf("\n\n");
    printf("\n\nA matriz multiplicada pelo vetor eh\n\n");
    for (i = 0; i < 3; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            printf("%d   ", (mat[i][j])*vet[i]);
        }
        printf("\n\n");
    }
    return (EXIT_SUCCESS);
}