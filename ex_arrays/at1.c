#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Faça um programa que sorteie um array com 100 números aleatórios entre 1 e 20. Depois,
peça ao usuário um valor X e imprima todos os números e quantas vezes o valor X foi
sorteado (Marque o símbolo * ao lado de cada aparição do valor X). Repita toda essa
operação para o mesmo conjunto de dados até X <= 0.*/

int main() {
	
	int n[100], x, cont=0;
	
	srand(time(NULL));

		for (int i = 0; i<100; i++) {
	
			n[i] = rand()%21;
			
			while (n[i]==0){
				
				n[i] = rand()%21;
			}
			
		printf("%02d\n", n[i]);
		}
	do {
		system("sleep 5");
		system("clear");
	
		printf("Informe um n°: \n");
		scanf(" %d", &x);
		printf("  \n");
		
		if (x>0) {
			
			for (int i = 0; i<100; i++) {
				
				if (n[i]==x){
					
					printf("%02d *\n", n[i]);
					cont++;
				} else {
					
					printf("%02d\n", n[i]);
				  }
			}
		
		printf("Número: %d , contagem: %d\n", x, cont);
		cont = 0;
		}
	} while ((x>0));
	return 0;
}