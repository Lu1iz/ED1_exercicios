//libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//structs
typedef struct {
	char nome[100];
	char num_conta[7];
	float saldo;
}ContaBancaria;

//funções
void wait();
int interface();
ContaBancaria abrir_nova_conta();
void validar_numero(ContaBancaria* nova, int ind);
int achou_conta(ContaBancaria* conta, int cont);
void mostrar_dados(ContaBancaria* conta, int cont);
void retirar_dinheiro(ContaBancaria* conta, int cont);
void depositar_dinheiro(ContaBancaria* conta, int cont);

//estrutura funções
void wait() {
	setbuf(stdin, NULL);
	getchar();
}

int interface() {
	system("clear");
	
	printf("===========================================================\n");
	printf("			BANCO AGIOTA\n");
	printf("===========================================================\n\n");
	printf("Opções: \n");
	int op;
	printf("		(1) - Abrir Nova Conta\n");
	printf("		(2) - Mostrar Dados da Conta\n");
	printf("		(3) - Retirada de Dinheiro\n");
	printf("		(4) - Depósito de Dinheiro\n");
	printf("----------------------------------------------------\n");
	printf("		(0) - ENCERRAR PROGRAMA\n");
	
	scanf(" %d", &op);
	return op;
}

ContaBancaria abrir_nova_conta() {
	system("clear");
	
	printf("===========================================================\n");
	printf("		Abrir Conta\n");
	printf("===========================================================\n\n");
	ContaBancaria nova;
	
	printf("Nome do Titular: ");
	scanf(" %[^\n]s", nova.nome);
	
	printf("Saldo: ");
	scanf(" %f", &nova.saldo);
		
	return nova;
}

void validar_numero(ContaBancaria* nova, int ind) {
	int A, B, C, D, V;

    srand(time(NULL));

    A = rand() % 10;
    B = rand() % 10;
    C = rand() % 10;
    D = rand() % 10;

    V = (A - B + C - D);
    
    if(V < 0)
		V = V *(-1);

    if (V >= 10) {
        int d1 = V / 10; 
        int d2 = V % 10;
        V = d1 + d2;
    }
    
    nova[ind].num_conta[0] = (A + '0');
    nova[ind].num_conta[1] = (B + '0');
    nova[ind].num_conta[2] = (C + '0');
    nova[ind].num_conta[3] = (D + '0');
    nova[ind].num_conta[4] = '-';
    nova[ind].num_conta[5] = (V + '0');
    nova[ind].num_conta[6] = 0;
}

int achou_conta(ContaBancaria* conta, int cont) {
	system("clear");
	
	printf("Informe o Nome do Titular: \n");
	char nm[50];
	
	do {
		scanf(" %[^\n]s", nm);
		
		for(int i=0; i<cont; i++) 
			if(!strcmp(nm, conta[i].nome)) 
				return i;
				
		printf("Conta não encontrada!\nTente novamente ou digite (-1) para sair...\n");
		
		if(!strcmp("-1", nm))
			return -1;
	}while(1);
}	

void mostrar_dados(ContaBancaria* conta, int cont) {
	int ind = achou_conta(conta, cont);
	
	if(ind == -1) {
		printf("Saindo...\n");
		wait();
		return;
	}
	system("clear");
	
	printf("===========================================================\n");
	printf("			Mostrar Dados da Conta\n");
	printf("===========================================================\n\n");
	
	printf("Nome do Titular: %s\n", conta[ind].nome);
	printf("Número da Conta: %s\n", conta[ind].num_conta);
	printf("Saldo: %.2f\n", conta[ind].saldo);
	
	wait();
	return;
}

void retirar_dinheiro(ContaBancaria* conta, int cont) {
	int ind = achou_conta(conta, cont);
	
	if(ind == -1) {
		printf("Saindo...\n");
		wait();
		return;
	}
	system("clear");
	
	printf("===========================================================\n");
	printf("		Retirar Dinheiro\n");
	printf("===========================================================\n\n");
	
	printf("Conta: %s\tNúmero: %s\tSaldo: %.2f\n\n", conta[ind].nome, conta[ind].num_conta, conta[ind].saldo);
	printf("Quanto deseja sacar: ");
	float saque;
	scanf(" %f", &saque);
	
	int val = 0;
	if(saque > conta[ind].saldo)
		do {
			printf("Saldo indisponível\nTente novamente ou digite (-1) para sair\n");
			scanf(" %f", &saque);
				
			if(saque == -1) {
				printf("Saque cancelado..\n");
				wait();
				return;
			}
			
			if(saque <= conta[ind].saldo)
				val = 1;
		}while(!val);	
		
	conta[ind].saldo = conta[ind].saldo - saque;
	
	printf("Saque Realizado com sucesso!\n");
	wait();
	return;	
}

void depositar_dinheiro(ContaBancaria* conta, int cont) {
	int ind = achou_conta(conta, cont);
	
	if(ind == -1) {
		printf("Saindo...\n");
		wait();
		return;
	}
	system("clear");
	
	printf("===========================================================\n");
	printf("			Deposito\n");
	printf("===========================================================\n\n");
	
	printf("Conta: %s\tNúmero: %s\tSaldo: %.2f\n\n", conta[ind].nome, conta[ind].num_conta, conta[ind].saldo);
	
	printf("Valor para deposito: ");
	float dep;
	scanf(" %f", &dep);
	
	int val = 0;
	if(dep <= 0)		
		do {
			printf("Deposito impossivel\nTente novamente ou digite (-1) para sair\n");
			scanf(" %f", &dep);
				
			if(dep == -1) {
				printf("Deposito cancelado..\n");
				wait();
				return;
			}
			
			if(dep > 0)
				val = 1;
		}while(!val);	
		
	conta[ind].saldo += dep;;
	
	printf("Deposito Realizado com sucesso!\n");
	wait();
	return;	
}

int main() {
	ContaBancaria conta[50];
	int cont_conta = 0;
	
	do {
		switch(interface()) {
			case 1: 
					conta[cont_conta] = abrir_nova_conta();
					validar_numero(conta, cont_conta);
					cont_conta++;
					break;
					
			case 2:	
					mostrar_dados(conta, cont_conta);
					break;
					
			case 3: 
					retirar_dinheiro(conta, cont_conta);
					break;
					
			case 4: 
					depositar_dinheiro(conta, cont_conta);
					break;
					
			case 0: 
					printf("Saindo do programa...\n");
					return 0;
					
			default: 
					printf("Opção Inválida!Tente novamente...\n");
					wait();
		}
	}while(1);
}
