#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Processo {
    int pid, tempo;
    struct Processo* prox;
    struct Processo* ant;
} Processo;

void wait() {
    setbuf(stdin, NULL);
    getchar();
}

int interface() {
    system("clear");
    printf("============= Interface =============\n\n");
    printf("Opções: \n");
    printf("\t1 - Cadastrar Novo Processo\n");
    printf("\t2 - Exibir Lista de Escalonamento\n");
    printf("\t3 - Executar Processo\n");
    printf("\t4 - Eliminar Processo\n");
    printf("------------------------------\n");
    printf("\t0 - Fechar Programa\n");

    int op;
    scanf(" %d", &op);
    return op;
}

Processo* setProcesso(Processo* esc) {
    srand(time(NULL));
    system("clear");
    printf("======== Cadastro ========\n\n");

    Processo* novo = malloc(sizeof(Processo));
    novo->tempo = 1 + rand() % 5;

    if (!esc) {
        novo->pid = 1;
        printf("PID: %d\tTempo: %d\n", novo->pid, novo->tempo);
        wait();

        novo->prox = novo;
        novo->ant = novo;
        esc = novo;
        return esc;
    }

    int maior_pid = 0;
    Processo* aux = esc;
    do {
        if (aux->pid > maior_pid)
            maior_pid = aux->pid;
        aux = aux->prox;
    } while (aux != esc);

    novo->pid = maior_pid + 1;
    printf("\nPID: %d\tTempo: %d\n", novo->pid, novo->tempo);
    wait();

    novo->prox = esc;
    novo->ant = esc->ant;
    esc->ant->prox = novo;
    esc->ant = novo;
    esc = novo;
    return esc;
}

void getProcesso(Processo* esc) {
    system("clear");
    printf("======== Lista ========\n\n");

    if (!esc) {
        printf("Lista vazia\n");
        wait();
        return;
    }

    Processo* aux = esc;
    do {
        printf("PID: %d\tTempo: %d\n", aux->pid, aux->tempo);
        aux = aux->prox;
    } while (aux != esc);

    wait();
}

Processo* execProcesso(Processo* esc) {
    system("clear");
    printf("======== Execução ========\n\n");

    if (!esc) {
        printf("Lista vazia\n");
        wait();
        return NULL;
    }

    Processo* x = esc;
    x->tempo--;

    if (!x->tempo) {
        printf("Processo de PID %d com tempo = %d foi finalizado!\n", x->pid, x->tempo);
        wait();

        if (x->prox == x) {
            free(x);
            return NULL;
        }

        esc = x->prox;
        x->ant->prox = x->prox;
        x->prox->ant = x->ant;
        free(x);
        return esc;
    }

    printf("Processo de PID %d com tempo = %d \n", x->pid, x->tempo);
    wait();

    esc = x->prox;
    return esc;
}

Processo* killProcesso(Processo* esc) {
    system("clear");
    printf("======== Eliminar Processo ========\n\n");

    if (!esc) {
        printf("Lista vazia\n");
        wait();
        return NULL;
    }

    int alvo;
    printf("Informe o PID do processo a ser eliminado: ");
    scanf(" %d", &alvo);

    Processo* pAlvo = esc;

    do {
        if (pAlvo->pid == alvo) {
            if (pAlvo->prox == pAlvo) {
                free(pAlvo);
                printf("\nProcesso eliminado!\n");
                wait();
                return NULL;
            }

            pAlvo->ant->prox = pAlvo->prox;
            pAlvo->prox->ant = pAlvo->ant;

            if (pAlvo == esc)
                esc = pAlvo->prox;

            free(pAlvo);
            printf("\nProcesso eliminado!\n");
            wait();
            return esc;
        }

        pAlvo = pAlvo->prox;
    } while (pAlvo != esc);

    printf("PID %d não encontrado!\n", alvo);
    wait();
    return esc;
}

int main() {
    Processo* esc = NULL;
	
    do {
        switch (interface()) {
            case 1: esc = setProcesso(esc); break;
            case 2: getProcesso(esc); break;
            case 3: esc = execProcesso(esc); break;
            case 4: esc = killProcesso(esc); break;
            case 0: printf("\nEncerrando..\n"); wait(); return 0;
            default: printf("\nOpção Inválida!\n"); wait(); break;
        }
    } while (1);
}
