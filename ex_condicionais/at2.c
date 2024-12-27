#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Programe uma calculadora IMC. Leia as informações de altura e peso e
informe ao usuário se ele está abaixo do peso, com peso normal, acima
do peso ou obeso.*/

int main() {
	
	float peso, h, imc;
	
	printf("Informe o seu peso: \n");
	scanf(" %f", &peso);
	printf("Informe a sua altura: \n");
	scanf(" %f", &h);
	
	imc = peso/(h*h);
	
	if(imc < 18.5) {
		
		printf("imc = %.3f .Abaixo do peso\n", imc);
		
		} else
			if(imc > 18.5 && imc < 24.9) {
				
				printf("imc = %.3f .Normal\n", imc);
				
				} else
					if(imc > 25 && imc < 29.9) {
						
						printf("imc = %.3f .Obesidade nível I\n", imc);
						
						} else
							if(imc > 30 && imc < 39.9) {
								
								printf("imc = %.3f .Obesidade nível II\n", imc);
								
								} else
									if(imc >= 40) {
										
										printf("imc = %.3f .Obesidade nível III\n", imc);
										
										}
	
	return 0;
	
	}
