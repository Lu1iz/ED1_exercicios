#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

/*Faça um programa em C que leia do usuário dois números inteiros X e Y.
Após isto, o programa deve imprimir X números aleatórios sorteados entre 0 e Y.*/

int main() {
	
	int x, y;
	
	printf("Informe um n°: \n");
	scanf(" %d", &x);
	printf("Informe outro n°: \n");
	scanf(" %d", &y);
	
	srand(time(NULL));
	for (int i = 0; i < x; i++) {
		
		int n = rand() % y;
		printf("%d\n", n);
	}
}