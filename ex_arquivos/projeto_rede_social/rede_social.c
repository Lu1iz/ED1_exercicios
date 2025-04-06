enum ARQUIVOS { USER, POST };

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "user.h"
#include "post.h"

#define MAX_ARQ 2

void wait() {
    setbuf(stdin, NULL);
    getchar();
}

FILE* open_file(char* nome) {
    FILE* arq = fopen(nome, "rb+");
    if (!arq)
        arq = fopen(nome, "wb+");
    if (!arq)
        printf("Programa não conseguiu abrir o arquivo!\n");
    return arq;
}

void close_file(FILE** arq) {
    for (int i = 0; i < MAX_ARQ; i++)
        fclose(arq[i]);
}

int interface() {
    system("clear");
    printf("-----------------------------------------------------------------\n");
    printf("\t\t\tREDE SOCIAL\n");
    printf("-----------------------------------------------------------------\n\n");

    printf("(1)- Novo Usuário\n");
    printf("(2)- Fazer Login\n");
    printf("(3)- Fechar Aplicação\n\n");

    printf("Opção: ");
    int op;
    scanf(" %d", &op);

    return op;
}

int main () {
    srand(time(NULL));

    FILE* arq[2];
    arq[USER] = open_file("arquivo_user.txt");
    arq[POST] = open_file("arquivo_post.txt");

    do {
        switch (interface()) {
            case 1:
                new_user(arq);
                break;

            case 2:
                controller_user(arq);
                break;

            case 3:
                printf("Fechando..\n");
                close_file(arq);
                return 0;

            default:
                printf("Opção Inválida! Tente novamente...\n");
                wait();
        }
    } while (1);
}
