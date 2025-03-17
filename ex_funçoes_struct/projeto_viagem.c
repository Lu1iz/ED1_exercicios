//libs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Structs
typedef struct {
    int cod, qnt_pass;
    char placa[9];
    int manutencao;
} Veiculo;

typedef struct {
    char cdd_origem[20], cdd_dest[20];
    int cod_vei, poltronas[100]; // 1 - livres ; 0 - ocupadas
    float valor;
} Viagem;

//Funções
void wait();
int interface();
Veiculo cadastrar_veiculo(int cod);
Viagem cadastrar_viagem(Veiculo* bus, int cont);
int busca_bus(Veiculo* bus, int cont);
void vender_passagem(Viagem* viagem, int cont, Veiculo* bus, int cont_bus);
int busca_origem(Viagem* viagem, int cont);
int busca_destino(Viagem* viagem, int cont, int ind);
void relatorio_veiculos(Veiculo* bus, int cont_bus, Viagem* viagem, int cont);
void relatorio_viagens_passagens(Viagem* viagem, int cont, Veiculo* bus, int cont_bus);
int print_poltronas(Viagem* viagem, int cont, Veiculo* bus, int cont_bus, int ind_bus, int ind);
void manutencao(Veiculo* bus, int cont_bus, Viagem* viagem, int cont);

// Funções estrutura
void wait() {
    setbuf(stdin, NULL);
    getchar();
}

int interface() {
    system("clear");

    printf("==================================================\n");
    printf("            VIAÇÃO BSI\n");
    printf("==================================================\n\n");
    printf("Opções: \n");
    printf("        1) Cadastrar Veículo na Frota\n");
    printf("        2) Cadastrar Viagem\n");
    printf("        3) Vender Passagem\n");
    printf("        4) Relatório: Frota de Veículos\n");
    printf("        5) Relatório: Viagens e Passagens Vendidas\n");
    printf("	6) Enviar para Manutenção\n");
    printf("--------------------------------------------------------\n");
    printf("        0) Sair do Programa\n\n");
    int op;
    scanf(" %d", &op);

    return op;
}

Veiculo cadastrar_veiculo(int cod) {
	system("clear");
	
	printf("==================================================\n");
    printf("            Cadastrar Veiculo\n");
    printf("==================================================\n\n");
	
	Veiculo novo;
	
	novo.cod = cod;
	
	for(int i=0; i<3; i++) 
		novo.placa[i] = 'A' + rand()%26;
	for(int i=3; i<8; i++)
		novo.placa[i] = '0' + rand()%10;
	novo.placa[8] = 0;	
	
	printf("Quantidade de poltronas: ");
	scanf(" %d", &novo.qnt_pass);
	
	novo.manutencao = 2;
	
	return novo;	
}

Viagem cadastrar_viagem(Veiculo* bus, int cont) {
	system("clear");
	
	printf("==================================================\n");
    printf("            Cadastrar Viagem\n");
    printf("==================================================\n\n");
    
    Viagem nova;
    
    int ind;
    
	ind = busca_bus(bus, cont);
    
	if(ind == -1) {
		printf("Cadastro Cancelado\nSaindo...\n");
		Viagem viagem_vazia = { "", "", 0, {0}, 0.0 };
		wait();
		return viagem_vazia;
	}
	
	if(bus[ind].manutencao == 1) {
		printf("Veiculo em manutenção!\n");
		Viagem viagem_vazia = { "", "", 0, {0}, 0.0 };
		wait();
		return viagem_vazia;
	}		
    
    nova.cod_vei = bus[ind].cod;
    
    for(int i=0; i<bus[ind].qnt_pass; i++) 
		nova.poltronas[i] = 1;

	for(int i=0; i<(bus[ind].qnt_pass /2); i++) {
		int indice;
		
		do {
			indice = rand() % bus[ind].qnt_pass; 
		} while(nova.poltronas[indice] == 0);

		nova.poltronas[indice] = 0; 
	}
    
    printf("\nInforme a cidade de origem: ");
    scanf(" %[^\n]s", nova.cdd_origem);
    printf("\nInforme a cidade de destino: ");
    scanf(" %[^\n]s", nova.cdd_dest);
    printf("\nInforme o preço da passagem: ");
    scanf(" %f", &nova.valor);
    
    return nova;
}

int busca_bus(Veiculo* bus, int cont) {
	printf("Informe o código do onibus: ");
	int cod;
	
	do {
		scanf(" %d", &cod);
		
		if(cod == -1) 
			return cod;
		
		for(int i=0; i<cont; i++) {
			if(cod == bus[i].cod) 
				return i;
		}
		
		printf("Código não encontrado! Tente novamente ou digite -1 para sair\n");	
					
	}while(1);
}

void vender_passagem(Viagem* viagem, int cont, Veiculo* bus, int cont_bus) {
	system("clear");
	
	printf("==================================================\n");
    printf("            Vender Passagem\n");
    printf("==================================================\n\n");
    
    int ind = busca_origem(viagem, cont);
    int ind_bus;
    
    if(ind == -1) {
		printf("\nVenda Cancelada\n");
		wait();
		return;
	}
	
	int x = busca_destino(viagem, cont, ind);
	
	if(!x) {
		printf("\nVenda Cancelada\n");
		wait();
		return;
	}
	
	if(x) {
		for(int i=0; i<cont_bus; i++) {
			if(viagem[ind].cod_vei == bus[i].cod)
				ind_bus = i;
		}
		
		int livre=0;
		for(int i=0; i<bus[ind_bus].qnt_pass; i++) 
			if(viagem[ind].poltronas[i] == 1) 
				livre++;
			
		if(!livre) {
			printf("Todas as poltronas estão ocupadas!\n");
			wait();
			return;
		}	
		
		system("clear");
		
		printf("==================================================\n");
		printf("            Vender Passagem\n");
		printf("==================================================\n\n");
		
		printf("%s -> %s\n", viagem[ind].cdd_origem, viagem[ind].cdd_dest);
	}
	printf("Valor Passagem: %.2f\n", viagem[ind].valor);
	
	printf("Pagar Valor: ");
	float pago, troco;
	
	int b=0;
	do {
		scanf(" %f", &pago);
		
		if(pago == -1) {
			printf("Venda Cancelada!\n");
			wait();
			return;
		}
		
		if(pago < viagem[ind].valor) 
			printf("Valor Insuficiente! Tente novamente ou digite (-1) para sair\n");
		
		if(pago >= viagem[ind].valor) {
			troco = pago - viagem[ind].valor;
			printf("\nTroco: %.2f\n", troco);
			b= 1;
		}
	}while(!b);
	
	print_poltronas(viagem, cont, bus, cont_bus, ind_bus, ind);
	
	printf("\nEscolha a poltrona: ");
	int poltrona, a=0;
	
	do{
		scanf(" %d", &poltrona);
		
		if(poltrona == -1) {
			printf("Venda Cancelada!\n");
			wait();
			return;
		}
		
		if(viagem[ind].poltronas[poltrona] == 0)
			printf("\nPoltrona já ocupada! Tente novamente ou digite (-1) para sair\n");
			
		if(viagem[ind].poltronas[poltrona] == 1) {
			viagem[ind].poltronas[poltrona] = 0;
			a = 1;
		}	
	}while(!a);
	
	printf("Venda Concluída com Sucesso!\n");
	wait();
	return;	 
}

int busca_origem(Viagem* viagem, int cont) {
	printf("Cidade de Origem: ");
	char origem[20];
	
	do {
		scanf(" %[^\n]s", origem);
				
		for(int i=0; i<cont; i++) {		
			
			if(!strcmp(origem, viagem[i].cdd_origem))
				return i;	
				
			if(!strcmp("exit", origem))
				return -1;
		}	
		
		printf("\nCidade de Origem não encontrada! Tente novamente ou digite (exit) para sair\n");
	}while(1);	
}

int busca_destino(Viagem* viagem, int cont, int ind) {
	printf("Cidade de Destino: ");
	char destino[20];
	
	do {
		scanf(" %[^\n]s", destino);
		
		if(!strcmp(destino, "exit"))
			return 0;
		
		if(!strcmp(destino, viagem[ind].cdd_dest))
			return 1;
			
		printf("\nCidade de Destino não encontrada! Tente novamente ou digite (exit) para sair\n");	
	}while(1);
}

void relatorio_veiculos(Veiculo* bus, int cont_bus, Viagem* viagem, int cont) {
	system("clear");
	
	printf("==================================================\n");
	printf("            Relatório: Frota de Veiculos\n");
	printf("==================================================\n\n");
	
	int ind_viagem;
	for(int i=0; i<cont_bus; i++) {
		printf("Código: %d\n", bus[i].cod);
		printf("Placa: %s\n", bus[i].placa);
		printf("Quantidade de Passageiros: %d\n", bus[i].qnt_pass);
		
		if(bus[i].manutencao == 2) {
			printf("Veiculo não está em manutenção\n");
		
			for(int j=0; j<cont; j++) {
				if(bus[i].cod == viagem[j].cod_vei) {
					ind_viagem = j;
					break;
				}	
				
				ind_viagem = -1;	
			}
			
			if(ind_viagem == -1)
				printf("Viagem: sem viagens no momento\n");
			else
				printf("Viagem: %s -> %s\n", viagem[ind_viagem].cdd_origem, viagem[ind_viagem].cdd_dest);
		}else
			printf("Veiculo em manutenção\n");
			
		printf("----------------------------------------------------------------\n\n");	
	}
	
	wait();
}

void relatorio_viagens_passagens(Viagem* viagem, int cont, Veiculo* bus, int cont_bus) {
	system("clear");
	
	printf("==================================================\n");
	printf("    Relatório: Viagens e Passagens Vendidas\n");
	printf("==================================================\n\n");
	
	int ind_bus;
	float t=0;
	for(int i=0; i<cont; i++) {
		printf("Cidade Origem: %s\n", viagem[i].cdd_origem);
		printf("Cidade Destino: %s\n", viagem[i].cdd_dest);
		printf("Códig Veiculo: %d\n", viagem[i].cod_vei);
		printf("Valor: %.2f\n", viagem[i].valor);
				
		for(int j=0; j<cont_bus; j++) 
			if(viagem[i].cod_vei == bus[j].cod)
				ind_bus = j;
		
		int ind = i;
				
		t += print_poltronas(viagem, cont, bus, cont_bus, ind_bus, ind);
		
		printf("\n-----------------------------------------------------------------\n\n");	
	}
	
	printf("\nArrecadação Total: %.2f\n", t);	
	wait();
}

int print_poltronas(Viagem* viagem, int cont, Veiculo* bus, int cont_bus, int ind_bus, int ind) {
    printf("Poltronas: \n");
    int livres = 0, ocupadas = 0;
    int total_assentos = bus[ind_bus].qnt_pass;
    float total = 0;

    for (int i = 0; i < total_assentos; i += 2) {
        if (i + 1 < total_assentos) 
            printf(" %2d   %2d\n", i, i + 1);
        else 
            printf(" %2d\n", i);

        for (int j = 0; j < 2; j++) {
            if (i + j < total_assentos) {
                if (viagem[ind].poltronas[i + j] == 1) {
                    livres++;
                    printf("[ ]  ");
                } else {
                    ocupadas++;
                    printf("[X]  ");
                }
            }
        }
        printf("\n"); 
    }

    printf("\nQuantidade de Poltronas livres: %d\n", livres);

    total = viagem[ind].valor * ocupadas;
    return total;
}

void manutencao(Veiculo* bus, int cont_bus, Viagem* viagem, int cont) {
    system("clear");

    printf("==================================================\n");
    printf("           Enviar para Manutenção\n");
    printf("==================================================\n\n");

    int ind = busca_bus(bus, cont_bus);
    
    if (ind == -1) {
        printf("\nManutenção Cancelada\n");
        wait();
        return;
    }

    int man;
    printf("Enviar para a manutenção? (1) - Sim ou (2) - Não: ");
    if (scanf("%d", &man) != 1 || (man != 1 && man != 2)) {
        printf("Entrada inválida. Operação cancelada.\n");
        wait();
        return;
    }

    if (man == 2) {
        printf("Veiculo %d não está em manutenção!\n", bus[ind].cod);
        wait();
        return;
    }

    if (bus[ind].manutencao == 1) {
        printf("Veiculo já está em manutenção!\n");
        wait();
        return;
    }

    int em_viagem = 0;
    int ind_viag = -1;
    
    for (int i = 0; i < cont; i++) {
        if (viagem[i].cod_vei == bus[ind].cod) {
            em_viagem = 1;
            ind_viag = i;
            break;
        }
    }

    if (!em_viagem) {
        printf("Veiculo enviado para a manutenção!\n");
        bus[ind].manutencao = 1;
        wait();
        return;
    }

    int substituto_encontrado = 0;
    for (int i = 0; i < cont_bus; i++) {
        if (i != ind && bus[i].qnt_pass >= bus[ind].qnt_pass && bus[i].manutencao == 2) {
            viagem[ind_viag].cod_vei = bus[i].cod;
            substituto_encontrado = 1;
            break;
        }
    }

    if (substituto_encontrado) {
        printf("Veiculo %d enviado para manutenção. Substituído pelo veículo %d.\n", bus[ind].cod, viagem[ind_viag].cod_vei);
        bus[ind].manutencao = 1;
    } else {
        printf("Veiculo está em viagem e não há reservas disponíveis!\n");
    }

    wait();
}


int main() {
    srand(time(NULL));

    Veiculo bus[50];
    Viagem viagem[50];
    int cont_bus = 0, cont_viagem = 0, codigo = 1;

    do {
        switch(interface()) {
            case 1:
                bus[cont_bus] = cadastrar_veiculo(codigo);
                codigo++;
                cont_bus++;
                break;

            case 2:
                viagem[cont_viagem] = cadastrar_viagem(bus, cont_bus);
                if (viagem[cont_viagem].cod_vei != 0)
                    cont_viagem++;
                break;

            case 3:
                vender_passagem(viagem, cont_viagem, bus, cont_bus);
                break;

            case 4:
                relatorio_veiculos(bus, cont_bus, viagem, cont_viagem);
                break;

            case 5:
				relatorio_viagens_passagens(viagem, cont_viagem, bus, cont_bus);
                break;
                
            case 6:
				manutencao(bus, cont_bus, viagem, cont_viagem);
				break;

            case 0:
                printf("Encerrando Programa...\n");
                return 0;

            default:
                printf("Opção Inválida! Tente novamente...\n");
        }
    }while(1);
    
    return 0;
}
