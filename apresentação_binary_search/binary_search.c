#include <stdio.h>
#include <stdlib.h>

#define N 10 

int main() {
    int arr[N] = {13, 99, 0, 20, 2, 7, 44, 49, 1, 11};
    int i, j, temp, inicio, fim, meio, alvo, encontrado = 0;

    for (i = 1; i < N; i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }

    printf("Digite um numero para buscar: ");
    scanf("%d", &alvo);

    inicio = 0;
    fim = N - 1;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (arr[meio] == alvo) { 
			printf("Numero %d encontrado na posicao %d.\n", alvo, meio);
            encontrado = 1;
            break;
        } else if (arr[meio] < alvo) {
            inicio = meio + 1; 
        } else {
            fim = meio - 1;
        }
    }
    
    if(encontrado) {
		printf("\nArray ordenado: ");
			for (i = 0; i < N; i++) 
				printf("%d ", arr[i]);
		printf("\n");
	}	

    if (!encontrado) 
        printf("Numero %d nao encontrado.\n", alvo);

    return 0;
}
