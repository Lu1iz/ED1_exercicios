#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	char desc[50];
	int estoque, cod; 
	float preco;
}Produto;

//funções
void wait();
int interface_loja();
Produto cadastrar_produto(Produto p[], int cont);
void ordem_bubble_sort(Produto* p, int cont);
int pesquisa_binaria(Produto p[], int cont, int alvo);
float venda_produto(Produto* p, int cont);
void listar_produtos(Produto p[], int cont);
void relatorio_vendas(Produto p[], int cont);
void carrinho_compras();

//estrutura
int interface_loja() {
	int opcao;
	
	system("clear");
	printf("----------------------------------------------------------\n");
	printf("			🏪 Lojinha do Sr. Zé 🏪\n");
	printf("----------------------------------------------------------\n");
	printf("(1) Cadastrar Produto\n");
	printf("(2) Carrinho de Compras\n");
	printf("(3) Relatório de Vendas\n");
	printf("----------------------------------------------------------\n");
	printf("(0) Sair do Programa\n\n");
	scanf(" %d", &opcao);
	
	return opcao;
}

int pesquisa_binaria(Produto p[], int cont, int alvo) {
    int esquerda = 0, direita = cont - 1;
    
    do {
        int meio = esquerda + (direita - esquerda) / 2;
        
        if (p[meio].cod == alvo)
            return meio;
        
        if (p[meio].cod < alvo)
            esquerda = meio + 1;
        else
            direita = meio - 1;

    } while (esquerda <= direita);
    
    return -1;
}

void wait() {
	setbuf(stdin, NULL);
	getchar();
}

Produto cadastrar_produto(Produto p[], int cont) {
    Produto novo;
    int cod;
    
    system("clear");
    
    printf("Novo Produto: \n\n");
    printf("\nCódigo: ");
    
    do {
        scanf(" %d", &cod);
        
        if (pesquisa_binaria(p, cont, cod) >= 0) { 
            printf("Código já existente!\nTente novamente... \n");
            continue;
        }
        
        novo.cod = cod;
        break;
    } while (1);    
     
	printf("\nDescrição: ");
	scanf(" %[^\n]s", novo.desc);
	printf("\nEstoque: ");
	scanf(" %d", &novo.estoque);
	printf("\nPreço: ");
	scanf(" %f", &novo.preco);
	printf("\n\nProduto Cadastrado com Sucesso ✅\n");
		
	wait();
    
    return novo;
}

void ordem_bubble_sort(Produto* p , int cont) {
    for (int i=0; i<cont; i++) 
		for (int j=0; j<cont-i; j++) 
            if(p[j].cod > p[j+1].cod) {
                Produto aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
            }
}

float venda_produto(Produto* p, int cont) {
	int comp, qnt, ind;
	
	system("clear");
	
	do {
		printf("Código (digite -1 para parar): ");
		scanf(" %d", &comp);
		printf("\n");
		
		if(comp != -1) {	
			ind = pesquisa_binaria(p, cont, comp);
			
			if (ind == -1) {  
				printf("Código %d não encontrado!\n", comp);
				wait();
				continue;	
			}
				
			printf("Venda %s , disponíveis %d unidades\n\n", p[ind].desc, p[ind].estoque);
			printf("Informe a quantidade: ");
			
			do {
				scanf(" %d", &qnt);
				
				if(!qnt)
					return 0;
										
				if(qnt > p[ind].estoque) {
					printf("\nQuantidade indisponível!\nTente novamente...\n");
					wait();
					continue;
				}
				
				break;
			}while(1);
		}	
		
		break;
	}while(1);	
	
	if(comp == -1)
		qnt = 0;
				
	float valor = p[ind].preco * qnt;	
	p[ind].estoque -= qnt;
	
	return valor;	
}

void carrinho_compras(Produto* p, int cont) {
	system("clear");
	
	printf("..............................................\n");
	printf("		🛒 Carrinho de Compras 🛒\n");
	printf("..............................................\n\n");
	
	float valor=0,total=0, pago=0;
		
	do {
		valor = venda_produto(p, cont);
		total += valor;
		
		if(!valor)
			break;
	}while(1);
	
	system("clear");		
	
	printf("..............................................\n");
	printf("		🛒 Carrinho de Compras 🛒\n");
	printf("..............................................\n\n");
	
	printf("Preço Venda: %.2f\n", total);	
	do {
		printf("Valor Pago: ");
		scanf(" %f", &pago);
			
		if(pago < total) {
			printf("\nValor Insuficiente!\nTente novamente...\n");
			wait();
			system("clear");
			continue;
		}else	
			break;
	}while(1);	
		
	float troco = pago - total;
	printf("Troco: %.2f\n", troco);

	printf("\nVenda Efetuada com Sucesso ✅\n");
				
	wait();
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
			case 1: 
				p[cont] = cadastrar_produto(p, cont);
                ordem_bubble_sort(p, cont);
                cont++;
				break;
					
			case 2: 
				carrinho_compras(p, cont);
				break;
					
			case 3: 
				relatorio_vendas(p, cont);
				break;
					
			case 0: 
				return 0;		
			
			default:
                printf("Opção inválida! Tente novamente.\n");
                wait();
		}
	}while(1);
}
