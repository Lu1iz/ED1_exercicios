#include <stdio.h>
#include <stdlib.h>

typedef struct Product{
	float val;
	char desc[50];
	int cod, qtde;
	struct Product* prox;
	struct Product* ant;
}Product;

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

int interface() {
	system("clear");
	printf("------------------------------------------------------\n");
	printf("\t\tMENU\n");
	printf("------------------------------------------------------\n\n");

	printf("Options: \n");
	printf("\t(1) - Cadastrar Produto\n");
	printf("\t(2) - Listar Produtos\n");
	printf("\t(3) - Deletar Produto\n\n");
	printf("\t--------------------------------------\n");
	printf("\t(0) - Fechar Programa\n");
	
	int op;
	scanf(" %d", &op);
	return op;
}
	
Product* setProduct(Product* prod) {
	system("clear");
	printf("--------------------Cadastrar Produto--------------------\n\n");
	
	Product* new = malloc(sizeof(Product));
	
	printf("Descrição: ");
	scanf(" %[^\n]s", new->desc);
	printf("\nCódigo: ");
	scanf(" %d", &new->cod);
	printf("\nValor: ");
	scanf(" %f", &new->val);
	printf("\nQtde: ");
	scanf(" %d", &new->qtde);
	
	if(!prod) {
		new->ant = new;
		new->prox = new;
		prod = new;
	}else {
		new->prox = prod;
		new->ant = prod->ant;
		prod->ant->prox = new;
		prod->ant = new;
		prod = new;
	}
	
	return prod;
}

void getProduct(Product* prod) {
	system("clear");
	printf("--------------------Listar Produtos--------------------\n\n");
	
	if(!prod) {
		printf("Lista Vazia !!\n");
		wait();
		return;
	}
	
	Product* atual = prod;
	
	do {
		printf("Descrição: %s\nCód: %d\nValor: %.2f\nQtde: %d\n\n", atual->desc, atual->cod, atual->val, atual->qtde);
		atual= atual->prox;
	}while(atual != prod);
	
	wait();
}

Product* delProduct(Product* prod) {
	system("clear");
	printf("--------------------Deletar Produto--------------------\n\n");
	
	if(!prod) {
		printf("Lista Vazia !!\n");
		wait();
		return NULL;
	}
	
	printf("Informe o cód do produto a ser removido: ");
	int alvo;
	scanf(" %d", &alvo);
	
	Product* pAlvo = prod;
	
	do {
		if(pAlvo->cod == alvo) {
			if(pAlvo->prox == pAlvo) {
				free(pAlvo);
				printf("\nProduto removido com sucesso!\n");
				wait();
				return NULL;
			}
			
			pAlvo->ant->prox = pAlvo->prox;
			pAlvo->prox->ant = pAlvo->ant;
			
			if(pAlvo == prod)
				prod = pAlvo->prox;
				
			free(pAlvo);
			printf("\nProduto removido com sucesso!\n");
			wait();
			return prod;
		}
		
		pAlvo = pAlvo->prox;
	}while(pAlvo != prod);
	
	printf("\nProduto de cód %d não cadastrado!\n", alvo);
	wait();
	return prod; 
}

int main() {
	Product* prod = NULL;
	
	do{
		switch(interface()) {
			case 1: prod = setProduct(prod);
					break;
					
			case 2: getProduct(prod);
					break;
					
			case 3: prod = delProduct(prod);
					break;
					
			case 0: printf("Saindo ..\n");
					wait();
					return 0;
					
			default: printf("Invalid option\nTry again!\n");
					 wait();		  
		}
	}while(1);
}

