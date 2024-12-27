#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Faça um programa que leia, em formato de string, um valor binário. O programa deve imprimir o
número lido no formato decimal correspondente.
Exemplo: 10110 == 22*/

int main() {
    char bin[20];
    int n = 0, c = 0, x = 0;

    printf("Digite o número binário: ");
    scanf(" %[^\n]s", bin);
    printf("\n");

    do {
        x = (bin[strlen(bin) - c - 1] - '0');

        n += (pow(2, c)) * x;

        c++; 
    } while (c < strlen(bin));

    printf("Em decimal: %d", n);

    return 0;
}