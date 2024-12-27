#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Faça um programa que leia 3 palavras. O programa deve imprimir as palavras em ordem alfabética.*/

int main() {
	
	char p1[20], p2[20], p3[20], t[20];
	
	printf("Digite a 1° palavra: ");
	scanf(" %[^\n]s", p1);
	printf("\n");
	
	printf("Digite a 2° palavra: ");
	scanf(" %[^\n]s", p2);
	printf("\n");
	
	printf("Digite a 3° palavra: ");
	scanf(" %[^\n]s", p3);
	printf("\n");

	if(strcmp(p1, p2) > 0) {
		
		strcpy(t, p2);
		strcpy(p2, p1);
		strcpy(p1, t);
	}
	
	if(strcmp(p1, p3) > 0) {
		
		strcpy(t, p3);
		strcpy(p3, p1);
		strcpy(p1, t);
	}
	
	if(strcmp(p2, p3) > 0) {
		
		strcpy(t, p3);
		strcpy(p3, p2);
		strcpy(p2, t);
	}
	
	printf("%s\n", p1);
	printf("%s\n", p2);
	printf("%s\n", p3);
	
	return 0;
}