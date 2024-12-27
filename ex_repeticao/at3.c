#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/*O número 5.832 possui a seguinte característica: 5+8+3+2 == 18 e 183 == 5.832
Faça um programa que verifique se existe(m) outro(s) número(s) de quatro
algarismos que possuem essa mesma característica.*/

int main() {
	
	int m, c, d, u, s;
	
	printf("Números com cacterísticas iguais: \n");
	
	for (int n = 1000; n<10000; n++) {
		
		m = n/ 1000;
		
		c = (n/100)%10;
		
		d = (n/10)%10;
		
		u = n%10;
		
		s = m+c+d+u;
		
		if (pow(s,3) == n) {
			
			printf("%d\n", n);
		}
	}
}