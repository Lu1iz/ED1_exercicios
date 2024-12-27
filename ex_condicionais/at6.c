#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Utilizando a estrutura Switch-Case faça um programa que leia do usuário
um valor inteiro e imprima o nome do mês correspondente (ou se o mês
não existe).*/

int main()
{

    int val;

    printf("Informe um valor: \n");
    scanf(" %d", &val);

    switch (val)
    {

    case 1:
        printf("Janeiro\n");
        break;

    case 2:
        printf("Fevereiro\n");
        break;

    case 3:
        printf("Março\n");
        break;

    case 4:
        printf("Abril\n");
        break;

    case 5:
        printf("Maio\n");
        break;

    case 6:
        printf("Junho\n");
        break;

    case 7:
        printf("Julho\n");
        break;

    case 8:
        printf("Agosto\n");
        break;

    case 9:
        printf("Setembro\n");
        break;

    case 10:
        printf("Outubro\n");
        break;

    case 11:
        printf("Novembro\n");
        break;

    case 12:
        printf("Dezembro\n");
        break;

    default:
        printf("Mês não existente\n");
    }

    return 0;
}