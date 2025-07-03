#include <stdio.h>
#include <stdlib.h>

typedef struct Product{
	int cod, qtde;
	char desc[50];
	float val;
	struct Product* prox;
	struct Product* ant;
}Product;

void wait() {
	setbuf(stdin, NULL);
	getchar();
}

int interface() {
	system("clear");
	
	printf("====================== Options ======================\n\n");
	printf("1- Cadastrar Produto\n");
	printf("2- Listar Produtos\n");
	printf("3- Apagar Produto\n");
	printf(".......................................\n");
	printf("0- Fechar Programa\n");
	
	int op;
	scanf(" %d", &op);
	return op;
}

Product* setProduct(Product* prod) {
	system("clear");
	printf("-------------------Cadastrar Product-------------------------\n\n");
	
	Product* new = malloc(sizeof(Product));
	
	printf("Código: ");
	scanf(" %d", &new->cod);
	printf("\nDescrição: ");
	scanf(" %[^\n]s", new->desc);
	printf("\nQtde: ");
	scanf(" %d", &new->qtde);
	printf("\nValor: ");
	scanf(" %f", &new->val);
	
	new->prox = prod;
	new->ant = NULL;
	
	if(prod)
		prod->ant = new;
		
	return new;	
}

void getProduct(Product* prod) {
	system("clear");
	printf("-------------------Listar Products-------------------------\n\n");
	
	if(!prod) {
		printf("Lista Vazia!\n");
		wait();
		return;
	}
	
	while(prod) {
		printf("Código: %d\nDescrição: %s\nQtde: %d\nValor: %.2f\n\n", prod->cod, prod->desc, prod->qtde, prod->val);
		prod = prod->prox;
	}
	wait();
	
	return;
}

Product* removeProduct(Product* prod) {
	system("clear");
	printf("-------------------Remover Produto-------------------------\n\n");
	
	if (!prod) {
		printf("Lista Vazia!\n");
		wait();
		return prod;
	}
	
	int alvo;
	printf("Digite o código do produto a ser excluído: ");
	scanf(" %d", &alvo);
	
	Product* atual = prod;

	while(atual) {
		if(atual->cod == alvo) {
			if(atual->ant == NULL) {
				prod = atual->prox;
				
				if(prod) 
					prod->ant = NULL;
			}else {
				atual->ant->prox = atual->prox;
				
				if(atual->prox)
					atual->prox->ant = atual->ant;
			}
			
			free(atual);
			printf("Produto removido com sucesso!\n");
			wait();
			return prod;
		}
		atual = atual->prox;
	}

	printf("Produto com código %d não encontrado!\n", alvo);
	wait();
	return prod;
}

int main() {
	Product *prod = NULL;
	
	do{
		switch(interface()) {
			case 1: prod = setProduct(prod);
					break;
					
			case 2: getProduct(prod);
					break;
					
			case 3: prod = removeProduct(prod);
					break;
					
			case 0: printf("Fechando Program...");
					wait();
					return 0;
					
			default: printf("Opção Inválida! Tente novamente!\n");
					 wait();
					 break;
		}
	}while(1);	
}

