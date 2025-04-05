typedef struct {
	char nome[20];
	int cod_discente;
	char email[50];
}Discente;

void wait();

int menu_discente() {
	system("clear");
	
	int opcao;
	
	printf("--------------------------------------------------------------------\n");
	printf("\t\t\tSistema DISCENTE\n");
	printf("--------------------------------------------------------------------\n\n");
	
	printf("COMANDOS: \n");
	printf("\t(1)- Cadastrar Discente\n");
	printf("\t(2)- Listar Discentes\n");
	printf("\t(3)- Consultar 1 Discente\n");
	printf("\t(4)- Editar Discente\n");
	printf("--------------------------------------------------------------------\n");
	printf("\t(0)- Retornar ao MENU PRINCIPAL\n\n");
	printf("Opção: ");
	scanf(" %d", &opcao);
	
	return opcao;
}

void cadastrar_discente(FILE** arq) {
	system("clear");
	
	Discente novo;
	
	printf("==============================================\n");
	printf("		Cadastro Discente\n");
	printf("==============================================\n\n");
	
	fseek(arq[ALUN], 0, SEEK_END);
	int tam = ftell(arq[ALUN]);
	novo.cod_discente = (tam/sizeof(Discente))+1;
	
	printf("\nMatrícula: %d\n", novo.cod_discente);
	printf("Nome: ");
	scanf(" %[^\n]s", novo.nome);
	printf("Email: ");
	scanf(" %[^\n]s", novo.email);
    
    if(fwrite(&novo, sizeof(Discente), 1, arq[ALUN])) {
		fflush(arq[ALUN]);
		printf("\nAluno Cadastrado com Sucesso!\n");
	}
	
	wait();
}

void lista_discente(FILE** arq) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Lista Discente\n");
	printf("==============================================\n\n");
	
	fseek(arq[ALUN], 0, SEEK_END);
	int tam = ftell(arq[ALUN]);
	if(!tam) {
		printf("Não há discentes cadastrados!\n");
		wait();
		return;
	}
	
	Discente a;
	
	fseek(arq[ALUN], 0, SEEK_SET);
	while(fread(&a, sizeof(Discente), 1, arq[ALUN])) {
		printf("Nome: %s\nCódigo: %d\n\n", a.nome, a.cod_discente);
		printf("----------------------------------------------------------------------\n");
	}
	
	wait();		
}

int verificar_discente(FILE** arq) {
    Discente aluno;
    
    printf("Digite o Nome do discente ((exit)- para sair): ");
    char nome[20];
    scanf(" %[^\n]s", nome);
    
    if(!strcmp(nome, "exit"))
		return -1;
    
    fseek(arq[ALUN], 0, SEEK_SET);
    while(fread(&aluno, sizeof(Discente), 1, arq[ALUN])) 
        if(!strcmp(aluno.nome, nome)) 
            return aluno.cod_discente;
  
    return 0;
}

void print_discente(FILE** arq, int cod_disciplina) {
	Matricula mat;
	Discente aluno;
	Disciplina disc;
	int a=0, b=0;
	
	rewind(arq[MAT]);
	while(fread(&mat, sizeof(Matricula), 1, arq[MAT])) {
		if(mat.cod_disciplina == cod_disciplina && mat.val == 1) {
			rewind(arq[DISC]);
			while(fread(&disc, sizeof(Disciplina), 1, arq[DISC])) {
				if (disc.cod_disciplina == cod_disciplina && disc.val == 1) {
					a=1;
					rewind(arq[ALUN]);
					while(fread(&aluno, sizeof(Discente), 1, arq[ALUN])) 
						if(aluno.cod_discente == mat.cod_discente) {
							b=1;
							printf("Código: %d\nNome: %s\nEmail: %s\nNota: %.2f\n", aluno.cod_discente, aluno.nome, aluno.email, mat.notas);
							printf("----------------------------------------------------------------------\n\n");
						}
				}
			}
		}
	}
	if(!a || !b)
		printf("Nenhum discente matriculado ou Matricula Cancelada!\n");
	
	wait();	
}

void print_matricula(FILE** arq) {
	Matricula mat;
	Discente aluno;
	Disciplina disc;
	
	rewind(arq[MAT]);
	while(fread(&mat, sizeof(Matricula), 1, arq[MAT]))
		if(mat.val == 1) {
			rewind(arq[DISC]);
			while(fread(&disc, sizeof(Disciplina), 1, arq[DISC]))
				if(disc.cod_disciplina == mat.cod_disciplina && disc.val == 1) {
					rewind(arq[ALUN]);
					while(fread(&aluno, sizeof(Discente), 1, arq[ALUN]))
						if(mat.cod_discente == aluno.cod_discente) {
							printf("Discente: %s -> Disciplina: %s\n", aluno.nome, disc.nome);
							printf("----------------------------------------------------------------------\n\n");
						}
				}
		}
}

void historico_discente(FILE** arq) {
	system("clear");
	
	printf("==============================================\n");
	printf("\t\tHistórico Do Discente\n");
	printf("==============================================\n\n");
	
	fseek(arq[ALUN], 0, SEEK_END);
	int tam = ftell(arq[ALUN]);
	if(!tam) {
		printf("Não há discentes cadastrados!\n");
		wait();
		return;
	}
	
	Discente alun;
	Matricula mat;
	Disciplina disc;
	int id, a=0, b=0;
	
	do {
		id = verificar_discente(arq);
		
		if(id == -1) {
			printf("Saindo do Histórico..\n");
			wait();
			return;
		}
		
		if(!id) {
			printf("Discente não encontrado! Tente novamente..\n");
			wait();
			continue;
		}
		
		break;
	}while(1);
	
	rewind(arq[ALUN]);
	while(fread(&alun, sizeof(Discente), 1, arq[ALUN]))
		if(id == alun.cod_discente)
			printf("\tDiscente:  %s\t| Código: %d\t| Email: %s\n", alun.nome, alun.cod_discente, alun.email);
			
	printf("Disciplinas: \n");		
	
	rewind(arq[MAT]);
	while(fread(&mat, sizeof(Matricula), 1, arq[MAT])) {
		if(mat.val == 1) {
			if(id == mat.cod_discente) {
				a=1;
			
				rewind(arq[DISC]);
				while(fread(&disc, sizeof(Disciplina), 1, arq[DISC]))
					if(mat.cod_disciplina == disc.cod_disciplina && disc.val != 0) {
						b=1;
					
						printf("%s\t| Código: %d\n", disc.nome, disc.cod_disciplina);
						printf("----------------------------------------------------------------------\n");
					}
			}		
		}
	}	
		
	if(!a || !b)
		printf("Nenhuma Disciplina!\n");	
		
	wait();	
}

void edit_discente(FILE** arq) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Editar Discente\n");
	printf("==============================================\n\n");
	
	fseek(arq[ALUN], 0, SEEK_END);
	int tam = ftell(arq[ALUN]);
	if(!tam) {
		printf("Não há discentes cadastrados!\n");
		wait();
		return;
	}
	
	Discente aluno;
	int id;
	do {
		id = verificar_discente(arq);
		
		if(id == -1) {
			printf("Saindo..\n");
			wait();
			return;
		}
		
		if(!id) {
			printf("Discente não encontrado! Tente novamente..\n");
			wait();
			continue;
		}
		
		break;
	}while(1);
	
	rewind(arq[ALUN]);
	while(fread(&aluno, sizeof(Discente), 1, arq[ALUN]))
		if(id == aluno.cod_discente) {
			fseek(arq[ALUN], -sizeof(Discente), SEEK_CUR);
			printf("Novo nome: ");
			scanf(" %[^\n]s", aluno.nome);
			printf("Novo email: ");
			scanf(" %[^\n]s", aluno.email);
			
			fwrite(&aluno, sizeof(Discente), 1, arq[ALUN]);
			fflush(arq[ALUN]);
			
			printf("Discente editado com Sucesso!\n");
			wait();
		}
}

void controller_discentes(FILE** arq) {
	do{
		switch(menu_discente()){
			case 1:	
					cadastrar_discente(arq);
					break;
					
			case 2: 
					lista_discente(arq);
					break;
					
			case 3: 
					historico_discente(arq);
					break;
					
			case 4: 
					edit_discente(arq);
					break;
								
			case 0: return;		
			
			default:
					printf("Opção Inválida! Tente novamente..\n");
					wait();
		}
	}while(1);
}
