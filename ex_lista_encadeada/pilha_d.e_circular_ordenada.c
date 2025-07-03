#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
	int cod, qtde;
	struct Item* prox;
	struct Item* ant;
}Item;

int interface() {
	system("clear");
	printf("++++++++++++++++++ MENU ++++++++++++++++++\n\n");
	printf("1 - Cadastrar\n");
	printf("2 - Listar\n");
	printf("3 - Excluir\n");
	printf("0 - Fechar Programa\n");
	
	int op;
	scanf(" %d", &op);
	return op;
}

void wait() {
	setbuf(stdin, NULL);
	getchar();
}

Item* setItem(Item* lst) {
	system("clear");
	printf("------------- Cadastro -------------\n\n");
	
	Item* new = malloc(sizeof(Item));
	printf("Cod: ");
	scanf(" %d", &new->cod);
	printf("\nQtde: ");
	scanf(" %d", &new->qtde);
	
	if(!lst) {
		new->ant = new;
		new->prox = new;
		lst = new;
		return lst;
	}
	
	Item* aux = lst;
	
	do {
		if(new->cod <= aux->cod) {
			new->prox = aux;
			new->ant = aux->ant;
			aux->ant->prox = new;
			aux->ant = new;
			
			if(aux == lst) lst = new;
				
			return lst;
		}
		
		aux = aux->prox;
	}while(aux != lst);
	
	new->prox = lst;
	new->ant = lst->ant;
	lst->ant->prox = new;
	lst->ant = new;
	
	return lst;
}

void getItem(Item* lst) {
	system("clear");
	printf("------------- Lista -------------\n\n");
	
	if(!lst) {
		printf("Lista vazia!\n");
		wait();
		return;
	}
	
	Item* a = lst;
	
	do {
		printf("Cod: %d\tQtde: %d\n", a->cod, a->qtde);
		a = a->prox;
	}while(a != lst);
	
	wait();
}

Item* delItem(Item* lst) {
	system("clear");
	printf("------------- Exclusão -------------\n\n");
	
	if(!lst) {
		printf("Lista vazia!\n");
		wait();
		return lst;
	}
	
	int alvo;
	printf("Informe o cod a ser excluido: ");
	scanf(" %d", &alvo);
	
	Item* pAlvo = lst;
	
	do {
		if(pAlvo->cod == alvo) {
			if(pAlvo->prox == pAlvo) {
				free(pAlvo);
				printf("\nExcluido com Sucesso!\n");
				wait();
				return NULL;
			}
			pAlvo->ant->prox = pAlvo->prox;
			pAlvo->prox->ant = pAlvo->ant;
			
			if(pAlvo == lst) lst = pAlvo->prox;
				
			free(pAlvo);
			printf("\nExluido com Sucesso!\n");
			wait();
			return lst;	
		}
		
		pAlvo = pAlvo->prox;
	}while(pAlvo != lst);

	printf("\nCod %d não encontrado!", alvo);
	wait();
	return lst;
}

int main() {
	Item* lst = NULL;
	
	do{
		switch(interface()) {
			case 1: lst = setItem(lst); break;
			case 2: getItem(lst); break;
			case 3: lst = delItem(lst); break;
			case 0: printf("\nSaindo ..\n"); wait(); return 13;
			default: printf("\nOption wrong\nTry again!\n"); wait(); break;
		}
	}while(1);
}


