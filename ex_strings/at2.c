#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gconio.h>

/*Construa um programa que peça para o usuário:
(i) Uma string S
(ii) Um caractere c1
(iii) Um caractere c2.
O programa deve substituir todas as ocorrências de c1 na string S pelo caractere c2.*/

int main() {
	
	char string[50], c1, c2;
	
	printf("Informe a string: ");
	scanf(" %[^\n]s", string);
	printf("\n");
	
	printf("Informe o c1: ");
	scanf(" %c", &c1);
	printf("\n");

	
	printf("Informe o c2: ");
	scanf(" %c", &c2);
	printf("\n");

	for(int i=0; i<strlen(string); i++)
		if(string[i] == c1)
			string[i] = c2;
		
	printf("%s", string);
	printf("\n");	
	
	return 0;	
}