#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Faça um programa que gera aleatoriamente uma aposta do jogo lotofácil (são 15 números
não-repetitivos no intervalo entre 01 e 25). Imprima também os 10 Nos não sorteados.*/

int main() {
    int ap[15]; 
    int todos[25]; 
    int num, i, j;
    int repetido;

    srand(time(NULL));

    for (i = 0; i < 25; i++) {
        todos[i] = i + 1;
    }

    for (i = 0; i < 15; i++) {
        do {
            num = rand() % 25 + 1; 
            repetido = 0; 

            for (j = 0; j < i; j++) {
                if (ap[j] == num) {
                    repetido = 1; 
                    break;
                }
            }
        } while (repetido); 

        ap[i] = num;
    }

    printf("Números sorteados: ");
    for (i = 0; i < 15; i++) {
        printf("%02d ", ap[i]);
    }
    printf("\n");

    printf("Números não sorteados: ");
    for (i = 0; i < 25; i++) {
        int sorteado = 0;

        for (j = 0; j < 15; j++) {
            if (todos[i] == ap[j]) {
                sorteado = 1; 
                break;
            }
        }

        if (!sorteado) {
            printf("%02d ", todos[i]);
        }
    }
    printf("\n");

    return 0;
}