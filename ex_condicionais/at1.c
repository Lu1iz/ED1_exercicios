
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*1. Faça um programa que leia dois números inteiros e imprima se eles são
múltiplos ou não.*/

int main() {
	
	int n1, n2;
	
	printf("Informe um n°: \n");
	scanf(" %d", &n1);
	printf("Informe outro n°: \n");
	scanf(" %d", &n2);
	
	if(n1 > n2) {
		
		if(n1%n2) {
			
			printf("Não multiplos!!\n");
			
			} else {
				
				printf("Multiplos!!\n");
				
				}
		
		}
		
		if(n2 > n1) {
			
			if(n2%n1) {
				
				printf("Não multiplos!!\n");
				
				} else {
					
					printf("Multiplos!!\n");
					
					}
			
			}		
	
	return 0;
	
	}