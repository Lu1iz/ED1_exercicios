#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

/*Gere uma matriz N x N onde os valores da diagonal principal sejam exatamente a soma
dos demais valores existentes na sua linha e coluna.*/

int main(){
	
	int n;
	
	printf("Informe o valor de NxN: \n");
	scanf(" %d", &n);
	
	system("clear");
	
	int matriz[n][n];
	
	srand(time(NULL));
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if(i!=j)
				matriz[i][j] = rand()%MAX;
			else
				matriz[i][j] = 0;
	
	for(int i=0; i<n; i++){
		
		int soma = 0;
		
		for(int j=0; j<n; j++)
			if(i!=j)
				soma += matriz[i][j];

		for(int j=0; j<n; j++)
			if(i!=j)
				soma += matriz[j][i];
					
	matriz[i][i] = soma;
	}
	
	for(int i=0; i<n; i++){
		
		for(int j=0; j<n; j++)
			printf("%02d ", matriz[i][j]);
			
		printf("\n");	
	}		
	
	return 0;
}