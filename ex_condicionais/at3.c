#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Leia três notas de um aluno e calcule a média ponderada, considerando
que o peso para a maior nota seja 4 e para as duas restantes, 3.
Imprima uma mensagem “APROVADO” se a média for maior ou igual a
6 ou “REPROVADO” caso contrário*/

int main()
{

	float n1, n2, n3, m;
	int maior;

	printf("Informe a 1° nota: \n");
	scanf(" %f", &n1);
	printf("Informe a 2° nota: \n");
	scanf(" %f", &n2);
	printf("Informe a 3° nota: \n");
	scanf(" %f", &n3);

	if (n1 >= n2 && n2 >= n3)
	{

		maior = 1;
	}

	if (n2 >= n1 && n2 >= n3)
	{

		maior = 2;
	}

	if (n3 >= n1 && n3 >= n2)
	{

		maior = 3;
	}

	switch (maior)
	{
	case 1:

		m = ((n1 * 4) + (n2 * 3) + (n3 * 3)) / (4 + 3 + 3);
		break;

	case 2:

		m = ((n2 * 4) + (n1 * 3) + (n3 * 3)) / (4 + 3 + 3);
		break;

	case 3:

		m = ((n3 * 4) + (n1 * 3) + (n2 * 3)) / (4 + 3 + 3);
		break;
	}

	if (m >= 6)
	{

		printf("média = %.1f .APROVADO\n", m);
	}
	else
	{

		printf("média = %.1f .REPROVADO\n", m);
	}

	return 0;
}
