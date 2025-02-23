#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char nome[10], cpf[12];
	int id;
	float h, p;
}Pessoas;

int main() {
	Pessoas reg[100];
	int cont=0;
	
	do {
		printf("\nNome ([exit] para parar): ");
		scanf(" %[^\n]s", reg[cont].nome);
		if(!strcmp(reg[cont].nome, "exit")) {
			while(getchar() != '\n');
			system("clear");
			break;
		}	
			
		printf("\nCPF: ");
		scanf(" %[^\n]s", reg[cont].cpf);
		printf("\nIdade: ");
		scanf(" %d", &reg[cont].id);
		printf("\nAltura: ");
		scanf(" %f", &reg[cont].h);
		printf("\nPeso: ");
		scanf(" %f", &reg[cont].p);
		
		int a=0;
		
		printf("\nSalvar? sim[1] ou não[0]: ");
		scanf(" %d", &a);
		
		if(a) 
			cont++;
			
		while(getchar() != '\n');
		system("clear");	
	}while(1);
		
	for (int i=0; i<cont-1; i++) 
		for (int j=0; j<cont-i-1; j++) 
			if (strcmp(reg[j].nome, reg[j+1].nome) >= 0) {
				Pessoas aux = reg[j];
				reg[j] = reg[j + 1];
				reg[j+1] = aux;
			}
	
	printf("Relatório: \n");
	for(int i=0; i<cont; i++)
		printf("\nNome: %s , CPF: %s , Idade: %d , Altura: %.2f , Peso: %.2f\n", reg[i].nome, reg[i].cpf, reg[i].id, reg[i].h, reg[i].p);

	return 0;
}
