#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/*A Fórmula de Bhaskara é uma das mais importantes da matemática, pois
é utilizada para resolução das equações de segundo grau. Faça um
programa que leia os valores A, B e C e calcule o resultado. (Ex.: Para
A=1, B=-5, C=6; Resultado >> X1==3; X2==2)*/

int main()
{
    float a, b, c, delt, x1, x2;
    
    printf("Digite o valor de a: \n");
    scanf("%f", &a);
    printf("Digite o valor de b: \n");
    scanf("%f", &b);
    printf("Digite o valor de c: \n");
    scanf("%f", &c);
    
    delt = (pow(b, 2)) - (4 * a * c);
    if (delt < 0) {
        printf("Não existem raízes reais, pois o discriminante é negativo.\n");
    } else {
        
        x1 = (-b + sqrt(delt)) / (2 * a); 
        x2 = (-b - sqrt(delt)) / (2 * a);
        
        printf("Delta = %f\nX1 = %f\nX2 = %f\n", delt, x1, x2);
    }
    
    return 0;
}