#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Problemas simples do cotidiano podem representar desafios para o
mundo computacional. Faça um programa que, dados três números
inteiros representando dia, mês e ano, imprima qual será o dia seguinte.*/

int main(){
	
	int d, m, a;
	
	printf("Informe o dia: \n");
	scanf(" %d", &d);
	printf("Informe o mês: \n");
	scanf(" %d", &m);
	printf("Informe o ano: \n");
	scanf(" %d", &a);
	
	if (d<32) {
		
		if (m<13) {
	
			if ((m==1) || (m==3) || (m==5) || (m==7) || (m==8) || (m==10)) {
		
				if (d<31) {
		
					printf("Dia atual: %d / %d / %d\n", d, m, a);
					printf("Dia seguinte: %d / %d / %d\n", ++d, m, a);
			
				} else
			
					if (d==31) {
				
						printf("Dia atual: %d / %d / %d\n", d, m, a);
						d = 1;
						printf("Dia seguinte: %d / %d / %d\n", d, ++m, a);
				
					}
			
			}else
	
			if ((m==4) || (m==6) || (m==9) || (m==11)) {
		
				if (d<30) {
			
					printf("Dia atual: %d / %d / %d\n", d, m, a);
					printf("Dia seguinte: %d / %d / %d\n", ++d, m, a);
			
				}else
			
					if (d==30) {
					
						printf("Dia atual: %d / %d / %d\n", d, m, a);
						d = 1;
						printf("Dia seguinte: %d / %d / %d\n", d, ++m, a);
					}
			
			}else
		
			if (m==12) {
			
				if (d<31) {
				
					printf("Dia atual: %d / %d / %d\n", d, m, a);
					printf("Dia seguinte: %d / %d / %d\n", ++d, m, a);
				
				}else
			
					if (d==31) {
					
						printf("Dia atual: %d / %d / %d\n", d, m, a);
						d = 1;
						m = 1;
						printf("Dia seguinte: %d / %d / %d\n", d, m, ++a);
					
					}
			
			}else
		
			if (m==2) {
			
				if (d<29) {
				
					if (d<28) {
				
					printf("Dia atual: %d / %d / %d\n", d, m, a);
					printf("Dia seguinte: %d / %d / %d\n", ++d, m, a);
				
					}else
			
						if (d==28) {
						
							printf("Dia atual: %d / %d / %d\n", d, m, a);
							d = 1;
							printf("Dia seguinte: %d / %d / %d\n", d, ++m, a);
						
						}
					
				}else {
			
				printf("Fervereiro só tem 28 dias!\n");
			}
			
			} 
			
		}else {
			
			printf("Não existe mais de 12 meses!\n");
		 }	
		
	}else {
	
	
		printf("Não existe mês com mais de 31 dias!\n");
	 }	
	 
	return 0;
		
}