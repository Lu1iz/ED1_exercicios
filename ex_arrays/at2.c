#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Um apostador joga um dado para o ar N vezes (N definido pelo usuário). Sabendo que um
dado possui 6 faces, faça um programa que simula o experimento. Como resultado,
imprima quantas vezes que cada face (não quais faces) caiu para cima e o % de cada face.*/

int main() {
    int cont[6] = {0}, n, face;
    float perc;

    printf("Digite quantas vezes o dado foi jogado: ");
    scanf("%d", &n);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        face = rand() % 6 + 1; 
        cont[face - 1]++; 
    }

    printf("\nResultados:\n");
    for (int i = 0; i < 6; i++) {
        perc = (float)cont[i] / n * 100; 
        printf("Face %d: %d vezes (%.2f%%)\n", i + 1, cont[i], perc);
    }

    return 0;
}