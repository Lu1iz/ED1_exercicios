#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Faça um programa que leia as 5 notas de um quesito da Escola de Samba,
descarte a maior e a menor nota, e apure a média das notas restantes.*/

int main()
{

    float n1, n2, n3, n4, n5, s, m, maior = -1000, menor = 99999;

    printf("Digite a 1° nota: \n");
    scanf(" %f", &n1);

    if (n1 > maior)
    {

        maior = n1;
    }else 
        if (n1 < menor)
        {

            menor = n1;
        }

    printf("Digite a 2° nota: \n");
    scanf(" %f", &n2);

    if (n2 > maior)
    {

        maior = n2;
    }else 
        if (n2 < menor)
        {

            menor = n2;
        }

    printf("Digite a 3° nota: \n");
    scanf(" %f", &n3);

    if (n3 > maior)
    {

        maior = n3;
    }else 
        if (n3 < menor)
        {

            menor = n3;
        }

    printf("Digite a 4° nota: \n");
    scanf(" %f", &n4);

    if (n4 > maior)
    {

        maior = n4;
    }else 
        if (n4 < menor)
        {

            menor = n4;
        }

    printf("Digite a 5° nota: \n");
    scanf(" %f", &n5);

    if (n5 > maior)
    {

        maior = n5;
    }else 
        if (n5 < menor)
        {

            menor = n5;
        }

    s = (n1 + n2 + n3 + n4 + n5) - (menor + maior);
    m = s / 3;

    printf("média = %.2f\n", m);

    return 0;
}