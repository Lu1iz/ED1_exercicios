#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Faça um programa que leia 3 valores (inteiros e positivos) de retas e
verifique se eles conseguem formar ou não um triângulo.*/

int main()
{
	
	int v1, v2, v3;
	
	printf("Digite um valor: \n");
	scanf(" %d", &v1);
	printf("Digite um outro valor: \n");
	scanf(" %d", &v2);
	printf("Digite um último valor: \n");
	scanf(" %d", &v3);
	
	if ((v1 + v2 > v3) && (v1 + v3 > v2) && (v2 + v3 > v1))
	{
		
		printf("Formam um triângulo!\n");
	}
	else
	{
		
		printf("Não formam um triângulo!\n");
	}
	
	return 0;
}