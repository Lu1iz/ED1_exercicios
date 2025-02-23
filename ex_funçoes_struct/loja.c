#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	char desc[50];
	int estoque, cod; 
	float preco;
}Produto;

void wait() {
	setbuf(stdin, NULL);
	getchar();
}

int interface_loja() {
	int opcao;
	
	system("clear");
	printf("----------------------------------------\n");
	printf("		Lojinha do Sr. Zé\n");
	printf("----------------------------------------\n");
	printf("(1) Cadastrar Produto\n");
	printf("(2) Vender Produto\n");
	printf("(3) Relatório de Vendas\n");
	printf("----------------------------------------\n");
	printf("(0) Sair do Programa\n\n");
	scanf(" %d", &opcao);
	
	return opcao;
}

Produto cadastrar_produto() {
	Produto novo;
	
	system("clear");
	
	printf("Novo Produto: \n\n");
	printf("Descrição: ");
	scanf(" %[^\n]s", novo.desc);
	printf("\nCódigo: ");
	scanf(" %d", &novo.cod);
	printf("\nEstoque: ");
	scanf(" %d", &novo.estoque);
	printf("\nPreço: ");
	scanf(" %f", &novo.preco);
	printf("\n\nProduto Cadastrado com Sucesso !\n");
	
	wait();
	
	return novo;
}

void venda_produto(Produto* p, int cont) {
	int comp, qnt, ind;
	
	system("clear");
	
	printf("Código: ");
	scanf(" %d", &comp);
	
	for(int i=0; i<cont; i++) {
		if(comp == p[i].cod) 
			ind = i;
		else 
			continue;
			
		printf("Venda %s , disponíveis %d unidades\n\n", p[ind].desc, p[ind].estoque);
		printf("Informe a quantidade: ");
		scanf(" %d", &qnt);
		printf("\n");
		
		if(qnt > p[ind].estoque) {
			printf("Quantidade indisponível!\n");
			printf("Venda Cancelada\n");
			wait();
			return;
		}
		
		float pago, total = p[ind].preco * qnt;
		
		printf("Preço Venda: %.2f\n", total);
		printf("Valor Pago: ");
		scanf(" %f", &pago);
		printf("\n");
		
		if(pago < total) {
			printf("Valor Insuficiente !\n");
			printf("Venda Cancelada !\n");
			wait();
			return;
		}	
		
		if(pago > total) {
			float troco = pago - total;
			printf("Troco: %.2f\n", troco);
		}
		
		printf("Venda Efetuada com Sucesso !\n");
		
		p[ind].estoque -= qnt;
		
		wait();
	}
}

void print_produto(Produto p) {	
	printf("Descrição: %s\n", p.desc);
	printf("Código: %d\n", p.cod);
	printf("Estoque: %d\n", p.estoque);
	printf("Preço: %.2f\n\n", p.preco);
}

void relatorio_vendas(Produto p[], int cont) {
	float bruto = 0;
	
	system("clear");
	
	printf("========================================\n");
	printf("		Relatório Loja: \n");
	printf("========================================\n\n");
	
	for(int i=0; i<cont; i++) {
		print_produto(p[i]);
		bruto += p[i].preco * p[i].estoque;
		printf("\n\n");
	}
	
	printf("Valor Bruto: %.2f\n", bruto);
	wait();
}

int main() {
	Produto p[100];
	int cont = 0;
	
	do {
		switch(interface_loja()) {
			case 1: p[cont++] = cadastrar_produto();
					break;
					
			case 2: venda_produto(p, cont);
					break;
					
			case 3: relatorio_vendas(p, cont);
					break;
					
			case 0: return 0;		
		}
	}while(1);
}