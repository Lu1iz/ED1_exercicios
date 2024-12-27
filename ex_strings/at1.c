#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gconio.h>

/*Faça um programa que simula um input para digitação de senha, oculto por caracteres ‘*’. Após
pressionar ENTER revele a senha digitada. Repita a operação 5 vezes na mesma execução. Dica: use a
função getch() da lib gconio.h*/

int main() {
	
	int senha[50], cont=0;
	
	for(int i=0; i<50; i++){
		
		senha[i] = getch();
				
		if(senha[i] == '\n')
			break;
		else{
			
			cont++;
			printf("*");
		}	
	}
	
	printf("\n");
	
	printf("Senha: ");
	for(int i=0; i<=cont; i++)
		printf("%d", senha[i]);
		
	printf("\n");
	
	return 0;	
}