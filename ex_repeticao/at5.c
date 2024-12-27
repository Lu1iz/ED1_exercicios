#include <stdio.h>

/*Faça um programa que imprima o calendário de um mês (no formato de
quadro). O usuário deve informar quantos dias tem no mês e o dia da semana em
que se inicia (considere 1==domingo; 2==segunda; 3==terça; etc...).*/

int main() {
    int dias_no_mes, dia_inicio;

    printf("Informe o número de dias no mês: ");
    scanf("%d", &dias_no_mes);

    printf("Informe o dia da semana de início (1=domingo, 2=segunda, ..., 7=sábado): ");
    scanf("%d", &dia_inicio);

    printf("Dom   Seg   Ter   Qua   Qui   Sex   Sab\n");

    for (int i = 1; i < dia_inicio; i++) {
        printf("      "); 
    }

    for (int dia = 1; dia <= dias_no_mes; dia++) {
        printf("%-6d", dia); 

        if ((dia + dia_inicio - 1) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}