#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/*Desenvolva um programa que gere e imprima vários números aleatórios entre
-100 e 100 (inclusive). O programa deve encerrar quando sortear o número zero.
Ao fim imprima a quantidade de números obtidos.*/

int main() {
    int n, count = 0;

    srand(time(NULL));

    printf("Números aleatórios gerados:\n");

    do {

        n = (rand() % 201) - 100;
        
        printf("%d ", n);
        
        count++;

    } while (n != 0);

    printf("\n\nQuantidade de números gerados: %d\n", count);

    return 0;
}