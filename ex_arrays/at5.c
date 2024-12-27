#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Sorteie nos aleatórios entre 1 e X para preencher uma tabela N x N (valor de N e X
definidos pelo usuário). Imprima os nos na tela em formato de tabela (linhas e colunas).*/

int main() {
    int N, X;

    printf("Digite o valor de NxN: ");
    scanf("%d", &N);
    printf("Digite o valor de X (intervalo de sorteio de números entre 1 e X): ");
    scanf("%d", &X);

    int tb[N][N];

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tb[i][j] = rand() % X + 1; 
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%02d\t", tb[i][j]); 
        }
        printf("\n"); 
    }

    return 0;
}