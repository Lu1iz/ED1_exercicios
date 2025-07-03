#include <stdio.h>
#include <stdlib.h>

typedef struct Produto{
	int qtde, cod;
	char desc[50];
	float valor;
	struct Produto* prox;
}Produto;

int menu() {
	system("clear");
	
	printf("============================================================\n");
	printf("\t\tMENU DE PRODUTOS\n");
	printf("============================================================\n\n");
	printf("1- Cadastrar Produto\n");
	printf("2- Listar Produtos\n");
	printf("3- Excluir Produto\n");
	printf("============================================================\n\n");
	printf("0- Fechar Programa\n");
	
	int op;
	scanf(" %d", &op);
	return op;
}

void wait() {
	setbuf(stdin, NULL);
	getchar();
}

Produto* setProduto(Produto* prod) {
	system("clear");
	
	printf("-----------------------------------------------\n");
	printf("\tCadastrar Produto\n");
	printf("-----------------------------------------------\n\n");
	
	Produto* new = malloc(sizeof(Produto));
	printf("Código: ");
	scanf(" %d", &new->cod);
	printf("\nDescrição: ");
	scanf(" %[^\n]s", new->desc);
	printf("\nQtde: ");
	scanf(" %d", &new->qtde);
	printf("\nValor: ");
	scanf(" %f", &new->valor);
	new->prox = prod;
	
	return new;
}	

void getProduto(Produto* prod) {
	system("clear");
	
	printf("-----------------------------------------------\n");
	printf("\tListar Produtos\n");
	printf("-----------------------------------------------\n\n");
	
	if(prod == NULL) {
		printf("Lista vazia!\n");
		wait();
		return;
	}
	
	while(prod) {
		printf("Código: %d\n", prod->cod);
		printf("Descrição: %s\n", prod->desc);
		printf("Qtde: %d\n", prod->qtde);
		printf("Valor: %.2f\n\n", prod->valor);
		
		prod = prod->prox;
	}
	
	wait();
}

Produto* removeProduto(Produto* prod) {
	system("clear");
	
	printf("-----------------------------------------------\n");
	printf("\tExcluir Produto\n");
	printf("-----------------------------------------------\n\n");

	if(prod == NULL) {
		printf("Lista vazia!\n");
		wait();
		return prod;
	}
	
	int alvo;
	printf("Digite o código para excluir: ");
	scanf(" %d", &alvo);
	
	Produto* anterior = NULL;
	Produto* atual = prod;
	
	while(atual) {
		if(atual->cod == alvo) {
			if(anterior) 
				anterior->prox = atual->prox;
			else 
				prod = atual->prox;
			
			free(atual);
			return prod;
		}
		anterior = atual;
		atual = atual->prox;
	}
	
	printf("\nCódigo %d inexistente!", alvo);
	wait();
	
	return prod;
}

int main() {
	Produto* prod = NULL;
	
	do {
		switch(menu()) {
			case 1: prod = setProduto(prod);
					break;
					
			case 2: getProduto(prod);
					break;
					
			case 3: prod = removeProduto(prod);
					break;
					
			case 0: return 0;
			
			default: printf("Opção inválida! Tente novamente!\n");
					 wait();
					 system("clear");
					 break;
		}
	}while(1);
}
