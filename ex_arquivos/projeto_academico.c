#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structs
typedef struct {
	char nome[20];
	int cod_discente;
}Discente;

typedef struct {
	char nome[20], professor[20];
	int cod_disciplina, ch;
}Disciplina;

typedef struct {
	int cod_discente;
	float notas;
	int cod_disciplina;
}Matricula;

//funções
void wait();
FILE* abrir_arquivo(char* nome);
void fechar_arquivo(FILE* arq_discentes, FILE* arq_disciplinas, FILE* arq_matriculas);
int interface();
void cadastrar_discente(FILE* arq);
void historico_discente(FILE* arq, FILE* arq_disciplina, FILE* arq_matricula);
void cadastrar_disciplina(FILE* arq);
void diario_disciplina(FILE* arq_disciplinas, FILE* arq_discentes, FILE* arq_matriculas);
void matricular_discente(FILE* arq_disciplina, FILE* arq_discente, FILE* arq_matriculas);
int verificar_discente(FILE* arq_discentes);
int verificar_disciplina(FILE* arq_disciplinas);
void lancar_nota(FILE* arq_discente, FILE* arq_disciplina, FILE* arq_matriculas);
void ordem_bubble_sort(Disciplina disc[], int c);

//estrutura funções
void wait() {
	setbuf(stdin, NULL);
	getchar();
}

FILE* abrir_arquivo(char* nome) {
	FILE* arq = NULL;
	arq = fopen(nome, "rb+");
	if(!arq)
		arq = fopen(nome, "wb+");
	if(!arq) {
		printf("Programa não conseguiu abrir o arquivo!\n");
		return NULL;
	}
	
	return arq;	
}

void fechar_arquivo(FILE* arq_discentes, FILE* arq_disciplinas, FILE* arq_matriculas) {
	fclose(arq_discentes);
	fclose(arq_disciplinas);
	fclose(arq_matriculas);
}

int interface() {
	system("clear");
	
	int opcao;
	
	printf("--------------------------------------------------------------------\n");
	printf("				Sistema Acadêmico\n");
	printf("--------------------------------------------------------------------\n\n");
	
	printf("COMANDOS: \n");
	printf("		   (1)- Cadastrar Discente\n");
	printf("		   (2)- Cadastrar Disciplina\n");
	printf("		   (3)- Matricular Discente\n");
	printf("		   (4)- Diário da Disciplina\n");
	printf("		   (5)- Histórico do Discente\n");
	printf("--------------------------------------------------------------------\n");
	printf("		   (0)- Sair do Programa\n\n");
	scanf(" %d", &opcao);
	
	return opcao;
}

void cadastrar_discente(FILE* arq) {
	system("clear");
	
	Discente novo;
	
	printf("==============================================\n");
	printf("		Cadastro Discente\n");
	printf("==============================================\n\n");
	
	fseek(arq, 0, SEEK_END);
	int tam = ftell(arq);
	novo.cod_discente = (tam/sizeof(Discente))+1;
	
	printf("\nMatrícula: %d\n", novo.cod_discente);
	printf("Nome: ");
	scanf(" %[^\n]s", novo.nome);
    
    if(fwrite(&novo, sizeof(Discente), 1, arq)) {
		fflush(arq);
		printf("\nAluno Cadastrado com Sucesso!\n");
	}	
}

void historico_discente(FILE* arq, FILE* arq_disciplina, FILE* arq_matricula) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Histórico Do Discente\n");
	printf("==============================================\n\n");
	
	Discente a;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&a, sizeof(Discente), 1, arq))
		printf("Nome: %s\nMatrícula: %d\n\n", a.nome, a.cod_discente);
		
	printf("Lançar nota? (1)- sim | (0)- não : ");
	int resp;
	scanf(" %d", &resp);
	
	if(!resp) 
		return;
		
	lancar_nota(arq, arq_disciplina, arq_matricula);	
}

void cadastrar_disciplina(FILE* arq) {
	system("clear");
	
	Disciplina nova;
	
	printf("==============================================\n");
	printf("		Cadastro Disciplinas\n");
	printf("==============================================\n\n");
	
	fseek(arq, 0, SEEK_END);
	int tam = ftell(arq);
	nova.cod_disciplina = (tam/sizeof(Disciplina))+1;
	
	printf("\nCódigo Disciplina: %d", nova.cod_disciplina);
	printf("\nNome: ");
	scanf(" %[^\n]s", nova.nome);
	printf("Carga Horária: ");
	scanf(" %d", &nova.ch);
	printf("Professor: ");
	scanf(" %[^\n]s", nova.professor);
			
    if(fwrite(&nova, sizeof(Disciplina), 1, arq)) {
		fflush(arq);
		printf("\nDisciplina Cadastrada com Sucesso!\n");
	}
}

void diario_disciplina(FILE* arq_disciplinas, FILE* arq_discentes, FILE* arq_matriculas) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Diário Disciplina\n");
	printf("==============================================\n\n");
	
    Disciplina disc[100];
    int cont= 0;
    
    Matricula mat;
    Discente aluno;
    int cod_disciplina;

    rewind(arq_disciplinas);
    printf("Disciplinas Cadastradas:\n");
    while(fread(&disc[cont], sizeof(Disciplina), 1, arq_disciplinas))
        cont++;
        
    if(!cont) {
		printf("Nenhuma Disciplina Cadastrada!\n");
		return;
	}
	
	ordem_bubble_sort(disc, cont);    
	
	for(int i=0; i<cont; i++)
		printf("Código: %d | Nome: %s\n", disc[i].cod_disciplina, disc[i].nome);

    printf("\nDigite o código da disciplina para detalhes: ");
    scanf("%d", &cod_disciplina);
    
    system("clear");
    for(int i=0; i<cont; i++) 
        if(disc[i].cod_disciplina == cod_disciplina) {
            printf("\nDisciplina: %s    Código: %d    Professor: %s    Carga Horária: %d\n", disc[i].nome, disc[i].cod_disciplina, disc[i].professor, disc[i].ch);
            printf("Alunos Matriculados:\n\n");
            
            rewind(arq_matriculas);
            while(fread(&mat, sizeof(Matricula), 1, arq_matriculas)) {
                if(mat.cod_disciplina == cod_disciplina) {
                    rewind(arq_discentes);
                    while(fread(&aluno, sizeof(Discente), 1, arq_discentes)) 
                        if(aluno.cod_discente == mat.cod_discente) 
                            printf("Código: %d    |    Nome: %s    |    Nota: %.2f\n", aluno.cod_discente, aluno.nome, mat.notas);
                }
            }
            break;
        }
    wait();
}

void matricular_discente(FILE* arq_disciplina, FILE* arq_discente, FILE* arq_matriculas) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Matriculas\n");
	printf("==============================================\n\n");
	
    Matricula nova;
    
    int id_discente;
	do {
		id_discente = verificar_discente(arq_discente);
		
		if(!id_discente) {
			printf("Discente não encontrado! Tente novamente..\n");
			continue;
		}
		
		break;
	}while(1);
       
    int id_disciplina;		
	do{	
		id_disciplina = verificar_disciplina(arq_disciplina);
		
		if(!id_disciplina) {
			printf("Disciplina não encontrada! Tente novamente..\n");
			continue;
		}
		
		break;
	}while(1);
	
	nova.cod_discente = id_discente;
	nova.cod_disciplina = id_disciplina;
	nova.notas = 0;
    
    fseek(arq_matriculas, 0, SEEK_END);
    fwrite(&nova, sizeof(Matricula), 1, arq_matriculas);
    fflush(arq_matriculas);
    printf("\nMatricula realizada com sucesso!\n");
    
    wait();
}

int verificar_discente(FILE* arq_discentes) {
    Discente aluno;
    
    printf("Digite o Nome do discente: ");
    char nome[20];
    scanf(" %[^\n]s", nome);
    
    fseek(arq_discentes, 0, SEEK_SET);
    while(fread(&aluno, sizeof(Discente), 1, arq_discentes)) 
        if(!strcmp(aluno.nome, nome)) 
            return aluno.cod_discente;
  
    return 0;
}

int verificar_disciplina(FILE* arq_disciplinas) {
    Disciplina disciplina;
    
    printf("Digite o código da disciplina: ");
    int cod_disciplina;
    scanf("%d", &cod_disciplina);
    
    fseek(arq_disciplinas, 0, SEEK_SET);
    while(fread(&disciplina, sizeof(Disciplina), 1, arq_disciplinas)) 
        if(disciplina.cod_disciplina == cod_disciplina) 
            return disciplina.cod_disciplina;
        
    return 0;
}

void lancar_nota(FILE* arq_discente, FILE* arq_disciplina, FILE* arq_matriculas) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Lançar Notas\n");
	printf("==============================================\n\n");
	
	Matricula mat;
	
	int id_discente;
	do {
		id_discente = verificar_discente(arq_discente);
		
		if(!id_discente) {
			printf("Discente não encontrado! Tente novamente..\n");
			continue;
		}
		
		break;
	}while(1);
       
    int id_disciplina;		
	do{	
		id_disciplina = verificar_disciplina(arq_disciplina);
		
		if(!id_disciplina) {
			printf("Disciplina não encontrada! Tente novamente..\n");
			continue;
		}
		
		break;
	}while(1);
	
	float nota;
	rewind(arq_matriculas);
    while(fread(&mat, sizeof(Matricula), 1, arq_matriculas)) {
        if(mat.cod_discente == id_discente && mat.cod_disciplina == id_disciplina) {
            printf("Digite a nova nota: ");
            scanf(" %f", &nota);
            
            mat.notas = nota;
            
            fseek(arq_matriculas, -sizeof(Matricula), SEEK_CUR);
            fwrite(&mat, sizeof(Matricula), 1, arq_matriculas);
            fflush(arq_matriculas);
            
            printf("Nota atualizada com sucesso!\n");
            wait();
            return;
        }
    }

    printf("Matrícula não encontrada!\n");
    wait();
}

void ordem_bubble_sort(Disciplina disc[], int c) {
	for(int i=0; i<c-1; i++)
		for(int j=0; j<c-i-1; j++)
			if(strcmp(disc[j].nome, disc[j+1].nome) > 0) {
				Disciplina temp = disc[j];
				disc[j] = disc[j+1];
				disc[j+1] = temp;
			}
}

int main() {
	FILE* arq_discentes = abrir_arquivo("arquivo_discentes_c.txt");
	FILE* arq_disciplinas = abrir_arquivo("arquivo_disciplinas_c.txt");
	FILE* arq_matriculas = abrir_arquivo("arquivo_matriculas_c.txt");
		
	do{
		switch(interface()) {
			case 1: 
					cadastrar_discente(arq_discentes);
					break;
					
			case 2:
					cadastrar_disciplina(arq_disciplinas);
					break;
					
			case 3:
					matricular_discente(arq_disciplinas, arq_discentes, arq_matriculas);
					break;
					
			
			case 4:
					diario_disciplina(arq_disciplinas, arq_discentes, arq_matriculas);
					break;
					
			case 5:
					historico_discente(arq_discentes, arq_disciplinas, arq_matriculas);
					break;
					
			case 0:
					fechar_arquivo(arq_discentes, arq_disciplinas, arq_matriculas);
					printf("Fechando Programa..\n");
					return 0;
					
			default:
					printf("Opção Inválida! Tente novamente..\n");
					wait();
		}
	}while(1);	
}
