#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Desenvolva um programa em C que faça a geração de senhas fortes. Uma senha forte é uma string
contendo entre 8 e 16 caracteres, com obrigatoriamente: 1 caractere numérico,
1 caractere maiúsculo, 1 minúsculo e 1 caractere especial. Imprima 10 senhas aleatórias.*/

int main() {
    char senha[20];
    int tam, ce, ma, mi;

    srand(time(NULL));

    for (int j = 0; j < 10; j++) {
        tam = 8 + rand() % 6; 

        for (int k = 0; k < tam; k++) {
            senha[k] = (rand() % 10) + '0';
        }

        ma = 65 + rand() % 26;  
        mi = 97 + rand() % 26;   
        ce = 33 + rand() % 15;  

        senha[rand() % tam] = ma;
        senha[rand() % tam] = mi;
        senha[rand() % tam] = ce;

        senha[tam] = '\0';

        printf("Senha %d: %s\n", j + 1, senha);
    }

    return 0;
}