#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Faça um programa que leia o nome completo de uma pessoa. O programa deve imprimir o nome com
todas as iniciais no formato maiúsculo, e demais letras no formato minúsculo.*/

int main() {
	
	char nome[50];
	
	printf("Digite seu nome: ");
	scanf(" %[^\n]s", nome);
	
	nome[0] -= 32;
	
	for(int i=0; i<strlen(nome); i++)
		if(nome[i] == ' ')
			nome[i+1] -= 32;
			
	printf("\n%s\n", nome);		
}