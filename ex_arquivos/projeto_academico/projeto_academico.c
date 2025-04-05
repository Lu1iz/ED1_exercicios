enum ARQUIVOS {ALUN, DISC, MAT};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricula.h"
#include "disciplina.h"
#include "discente.h"

#define MAX_ARQ 3

void wait() {
	setbuf(stdin, NULL);
	getchar();
}

FILE* abrirArquivo(char* nome){
	FILE* arq = NULL;
	arq = fopen(nome,"rb+");
	if(!arq)
		arq = fopen(nome,"wb+");
	if(!arq)
		printf("Programa não conseguiu abrir o arquivo!\n");
		
	return arq;
}

void fechar_arquivo(FILE** arq) {
	for(int i=0; i<MAX_ARQ; i++)
		fclose(arq[i]);
}

int interface() {
	system("clear");
	
	int opcao;
	
	printf("--------------------------------------------------------------------\n");
	printf("\t\t\tSistema Acadêmico\n");
	printf("--------------------------------------------------------------------\n\n");
	
	printf("COMANDOS: \n");
	printf("\t(1)- Discentes\n");
	printf("\t(2)- Disciplinas\n");
	printf("\t(3)- Matriculas\n");
	printf("--------------------------------------------------------------------\n");
	printf("\t(0)- Sair do Programa\n\n");
	printf("Modulo: ");
	scanf(" %d", &opcao);
	
	return opcao;
}

int main() {
	FILE* arq[3];
	arq[ALUN] = abrirArquivo("arquivo_discentes_c.txt");
	arq[DISC] = abrirArquivo("arquivo_disciplinas_c.txt");
	arq[MAT] = abrirArquivo("arquivo_matriculas_c.txt");
				
	do{
		switch(interface()) {
			case 1: 
					controller_discentes(arq);
					break;
					
			case 2: 
					controller_disciplina(arq); 
					break;
					
			case 3: 
					controller_matricula(arq);
					break;
					
			case 0:
					fechar_arquivo(arq);
					printf("Fechando Programa..\n");
					return 0;
					
			default:
					printf("Opção Inválida! Tente novamente..\n");
					wait();
		}
	}while(1);	
}
