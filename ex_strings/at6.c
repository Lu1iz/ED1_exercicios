#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Faça um programa que alimenta uma matriz [10][5] com nos aleatórios entre 0 e 1000. Faça a
impressão dos valores em formato de tabela, e cuja largura de cada coluna contenha exatamente o
tamanho de N espaços (N deverá ser informado pelo usuário). Dica: sprintf()*/

int main() {
	
	int matriz[10][5];
	int n;
	
	srand(time(NULL));
	for(int i=0; i<5; i++)
		for(int j=0; j<10; j++)
			matriz[j][i] = rand()%1001;
			
	printf("Informe o tamanho N de espaços: ");
	scanf(" %d", &n);
	printf("\n");
	
	while(getchar() != '\n');
	system("clear");
	
	for(int i=0; i<5; i++){
		
		for(int j=0; j<10; j++){
			
			char buffer[100];
			sprintf(buffer, "%*d", n, matriz[i][j]);
			printf("%s ", buffer);
		}	
			
		printf("\n");	
	}		
	
	return 0;	
}