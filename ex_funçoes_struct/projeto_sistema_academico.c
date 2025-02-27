//PROJETO SISTEMA ACADEMICO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS
typedef struct {
	char nome[50];
	int matr, notas[100][2];
	float coef_rend;
	int cont_notas;
}Discente;

typedef struct {
	int cod, ch;
	char nome[50];
	int alunos[50];
	int cont_alunos;
}Disciplina;

//FUNÇÕES
int interface();
void wait();
int achou_disciplina(Disciplina mat[], int cont_disciplina);
int achou_aluno(Discente alunos[], int cont_alunos);
Disciplina cadastrar_disciplina(int cont_cod);
Discente cadastrar_aluno(int cont_matr);
void matricular_aluno(Disciplina* mat, Discente* aluno, int cont_disciplina, int cont_alunos);
void lancar_notas(Discente* alunos, Disciplina* mat, int cont_discente, int cont_disciplina);
void coeficiencia_rendimento(Discente alunos[], int cont_discente, Disciplina mat[], int cont_disciplina);
void diario_disciplina(Disciplina mat[], int cont_disciplina, Discente aluno[], int cont_discentes);
void historico_aluno(Discente alunos[], int cont_discentes, Disciplina mat[], int cont_disciplina);
void ordem_bubble_sort(Discente alunos[], int cont_discente);
void ranking_cr(Discente alunos[], int cont_discente);

//ESTRUTURA FUNÇÕES
int interface() {
	system("clear");
	
	int opcao;
	
	printf("--------------------------------------------------------------------\n");
	printf("				Sistema Acadêmico\n");
	printf("--------------------------------------------------------------------\n\n");
	
	printf("COMANDOS: \n");
	printf("		   (1)- Cadastrar Disciplina\n");
	printf("		   (2)- Cadastrar Aluno\n");
	printf("		   (3)- Matricular Aluno\n");
	printf("		   (4)- Lançar Notas\n");
	printf("		   (5)- Diário da Disciplina\n");
	printf("		   (6)- Histórico do Aluno\n");
	printf("		   (7)- Ranking de Coeficiente de Rendimento\n");
	printf("--------------------------------------------------------------------\n");
	printf("		   (0)- Sair do Programa\n\n");
	scanf(" %d", &opcao);
	
	return opcao;
}

void wait() {
	setbuf(stdin, NULL);
	getchar();
}

int achou_disciplina(Disciplina mat[], int cont_disciplina) {
	printf("Digite o nome da disciplina: ");
	char nom_disc[50];
	
	do {
		scanf(" %[^\n]s", nom_disc);
		
		if(strcmp(nom_disc, "exit") == 0)
			break;
				
		for(int i=0; i<cont_disciplina; i++)			
			if(strcmp(mat[i].nome, nom_disc) == 0) 
				return i;
		
		printf("\nNome inexistente!\nTente novamente ou digite (exit) para sair\n");
	}while(1);
	
	return -1;
}

int achou_aluno(Discente alunos[], int cont_alunos) {
	printf("Digite o Nome do discente: ");
	char nome_alu[50];
	
	do {	
		scanf(" %[^\n]s", nome_alu);
		
		if(strcmp(nome_alu, "exit") == 0)
			break;
		
	   for(int j=0; j<cont_alunos; j++)
			if(strcmp(alunos[j].nome, nome_alu) == 0)
				return j;
			
		printf("\nNome inexistente!\nTente novamente ou digite (exit) para sair\n");	
	}while(1);
	
	return -1;
}

Disciplina cadastrar_disciplina(int cont_cod) {
	system("clear");
	
	Disciplina nova;
	
	printf("==============================================\n");
	printf("		Cadastro Disciplinas\n");
	printf("==============================================\n\n");
	
	printf("Nome: ");
	scanf(" %[^\n]s", nova.nome);
	printf("\nCarga Horária: ");
	scanf(" %d", &nova.ch);
	nova.cont_alunos= 0;
	nova.cod = cont_cod;
	
	printf("\nDisciplina Cadastrada com Sucesso!\n");
	wait();
	
	return nova;
}

Discente cadastrar_aluno(int cont_matr) {
	system("clear");
	
	Discente novo;
	
	printf("==============================================\n");
	printf("		Cadastro Aluno\n");
	printf("==============================================\n\n");
	
	printf("Nome: ");
	scanf(" %[^\n]s", novo.nome);
	novo.matr = cont_matr;
	novo.cont_notas = 0;
	novo.coef_rend = -1;
	
	for (int i=0; i<100; i++) {
        novo.notas[i][0] = -1;
        novo.notas[i][1] = -1;
    }
    
    printf("\nAluno Cadastrado com Sucesso!\n");
    wait();
	
	return novo;
}

void matricular_aluno(Disciplina* mat, Discente* aluno, int cont_disciplina, int cont_alunos) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Matrículas\n");
	printf("==============================================\n\n");
	
	int id_disc = achou_disciplina(mat, cont_disciplina);
	
	if(id_disc < 0) {
		printf("\nMatrícula Cancelada!\n");
		wait();
		return;
	}	
	
	int id_alu = achou_aluno(aluno, cont_alunos);

	if(id_alu < 0) {
		printf("\nMatrícula Cancelada!\n");
		wait();
		return;
	}	
			
	mat[id_disc].alunos[mat[id_disc].cont_alunos] = aluno[id_alu].matr;
	mat[id_disc].cont_alunos++;
	
	printf("\nAluno matriculado com sucesso!\n");
	wait();
}

void lancar_notas(Discente* alunos, Disciplina* mat, int cont_discente, int cont_disciplina) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Lançar Notas\n");
	printf("==============================================\n\n");
	
	int id_disc = achou_disciplina(mat, cont_disciplina);
	
	if(id_disc < 0) {
		printf("\nNota Cancelada!\n");
		wait();
		return;
	}
	
	int id_alu = achou_aluno(alunos, cont_discente);
	
	if(id_alu < 0) {
		printf("\nNota Cancelada!\n");
		wait();
		return;
	}
	
	int matriculado = 0;
	for(int i=0; i<mat[id_disc].cont_alunos; i++)
		if(alunos[id_alu].matr == mat[id_disc].alunos[i]) {
			matriculado = 1;
			break;
		}	
		
	if(!matriculado) {	
		printf("\nAluno não matriculado nessa disciplina!\n");
		wait();	
		return;	
	}	
	
	for (int k=0; k<alunos[id_alu].cont_notas; k++) 
		if (alunos[id_alu].notas[k][0] == mat[id_disc].cod) {
			printf("\nNota do Aluno já lançada!\n");
			wait();
			return;
		}
		
	printf("\nDigite a nota: ");
	int n;
	scanf(" %d", &n);
	
	alunos[id_alu].notas[alunos[id_alu].cont_notas][0] = mat[id_disc].cod;
    alunos[id_alu].notas[alunos[id_alu].cont_notas][1] = n;
    alunos[id_alu].cont_notas++;
    printf("\nNota lançada com sucesso!\n");
    
    wait();
    
	coeficiencia_rendimento(alunos, cont_discente, mat, cont_disciplina);
}

void coeficiencia_rendimento(Discente* alunos, int cont_discente, Disciplina mat[], int cont_disciplina) {
	for(int i=0; i<cont_discente; i++) {
		float soma = 0;
		int qnt = 0;
		
		for(int j=0; j<alunos[i].cont_notas; j++) {
			soma += alunos[i].notas[j][1];
			qnt++;
		} 
		
		if(qnt > 0)
			alunos[i].coef_rend = soma/qnt;
		else
			alunos[i].coef_rend = 0;
	}
	
	ordem_bubble_sort(alunos, cont_discente);
}

void diario_disciplina(Disciplina mat[], int cont_disciplina, Discente aluno[], int cont_discentes) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Diário Disciplina\n");
	printf("==============================================\n\n");
	
	int id_disc = achou_disciplina(mat, cont_disciplina);
	
	if(id_disc < 0) {
		printf("\nSaindo de Diário Disciplina!\n");
		wait();
		return;
	}	
	
	printf("Disciplina %s , Carga Horária: %d horas\n\n", mat[id_disc].nome, mat[id_disc].ch);
	
	for (int i=0; i<mat[id_disc].cont_alunos; i++) {
		int matr = mat[id_disc].alunos[i];

		for (int j=0; j<cont_discentes; j++) {
			if (aluno[j].matr == matr) {
				printf("Aluno: %s, Matrícula: %d, Nota: ", aluno[j].nome, aluno[j].matr);
            
				int nota = -1;
				for (int k=0; k<aluno[j].cont_notas; k++) {
					if (aluno[j].notas[k][0] == mat[id_disc].cod) {
						nota = aluno[j].notas[k][1];
						break;
					}
				}
				printf("%d\n\n", nota == -1 ? 0 : nota);
			}
		}
	}
	
	wait();
}

void historico_aluno(Discente alunos[], int cont_discentes, Disciplina mat[], int cont_disciplina) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Histórico Do Aluno\n");
	printf("==============================================\n\n");
	
	int id_alu = achou_aluno(alunos, cont_discentes);
	
	if(id_alu < 0) {
		printf("\nSaindo do Histórico do Aluno!\n");
		wait();
		return;
	}	
	
	for(int i=0; i<cont_disciplina; i++) {
		for(int j=0; j<mat[i].cont_alunos; j++) {
			if(alunos[id_alu].matr == mat[i].alunos[j]) {
				printf("\nDisciplina: %s, Código: %d, Nota: ", mat[i].nome, mat[i].cod);
				
				int nota = -1;
				for (int k=0; k<alunos[id_alu].cont_notas; k++) {
					if (alunos[id_alu].notas[k][0] == mat[i].cod) {
						nota = alunos[id_alu].notas[k][1];
						break;
					}
				}
				printf("%d\n\n", nota == -1 ? 0 : nota);
			}
		}
	}
	
	wait();
}

void ordem_bubble_sort(Discente alunos[], int cont_discente) {
	for (int i=0; i<cont_discente-1; i++) 
		for (int j=0; j<cont_discente-i-1; j++) 
            if(alunos[j].coef_rend < alunos[j+1].coef_rend) {
                Discente aux = alunos[j];
                alunos[j] = alunos[j+1];
                alunos[j+1] = aux;
            }
}

void ranking_cr(Discente alunos[], int cont_discente) {
	system("clear");
	
	printf("===================================================================\n");
	printf("		Ranking De Coeficiente de Rendimento\n");
	printf("===================================================================\n\n");
	
	for(int i=0; i<cont_discente; i++) {
		if(alunos[i].coef_rend < 0)
			alunos[i].coef_rend = 0;
		
		printf("Aluno: %s, Coeficiente de Rendimento: %.2f\n", alunos[i].nome, alunos[i].coef_rend);
	}
	
	wait();
}

int main() {
	system("clear");
	
	Disciplina mat[100];
	int cont_disciplina = 0, cont_cod = 1;
	
	Discente aluno[100];
	int cont_discentes = 0, cont_matr = 1;
	
	do {
		switch(interface()) {
			case 1: 
					mat[cont_disciplina] = cadastrar_disciplina(cont_cod);
					cont_disciplina++;
					cont_cod++;
					break;
					
			case 2:
					aluno[cont_discentes] = cadastrar_aluno(cont_matr);
					cont_discentes++;
					cont_matr++;
					break;
					
			case 3: 
					matricular_aluno(mat, aluno, cont_disciplina, cont_discentes);
					break;
					
			case 4:
					lancar_notas(aluno, mat, cont_discentes, cont_disciplina);
					break;
					
			case 5: 
					diario_disciplina(mat, cont_disciplina, aluno, cont_discentes);
					break;
					
			case 6:
					historico_aluno(aluno, cont_discentes, mat, cont_disciplina);
					break;
					
			case 7:
					ranking_cr(aluno, cont_discentes);
					break;
					
			case 0:
					printf("\nSaindo do programa...\n");
					return 0;
		
					
			default:
					printf("\nOpção inválida!\nTente novamente...\n");
					wait();
		}
	}while(1);	
}
