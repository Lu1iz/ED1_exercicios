#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Declare um Array contendo N números inteiros aleatórios no intervalo entre 0 e 99.
Imprima o vetor sorteado originalmente, e faça a ordenação utilizando os seguintes
algoritmos. Para cada versão, contabilize o número de comparações e permutações
(trocas) necessárias para a ordenação do Array.
	(b) Selection Sort*/

int main() {
	int n, comp=0, perm=0;
	
	printf("Informe o valor de N: ");
	scanf(" %d", &n);
	printf("\n");
	
	int arr[n];
	
	srand(time(NULL));
	
	printf("Original: ");
	for(int i=0; i<n; i++) {
		arr[i]= rand()%100;
		printf("%d ", arr[i]);
	}
	printf("\n");
		
	 for (int i=0; i<n-1; i++) {
        int mind= i; 

        for (int j=i+1; j<n; j++) {
            comp++; 
            
            if (arr[j] < arr[mind]) {
                mind= j;
            }
        }

        if (mind != i) {
            int temp = arr[i];
            arr[i] = arr[mind];
            arr[mind] = temp;
            perm++;
        }
    }

    printf("Ordenado (Selection Sort): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Comparações: %d\n", comp);
    printf("Permutações: %d\n", perm);
		
	return 0;
}
