typedef struct {
	char nome[20], professor[20];
	int cod_disciplina, ch;
	int val;
}Disciplina;

void wait();
void print_discente(FILE** arq, int cod_disciplina);

int menu_disciplina() {
	system("clear");
	
	int opcao;
	
	printf("--------------------------------------------------------------------\n");
	printf("\t\t\tSistema DISCIPLINA\n");
	printf("--------------------------------------------------------------------\n\n");
	
	printf("COMANDOS: \n");
	printf("\t(1)- Cadastrar Disciplina\n");
	printf("\t(2)- Relatório de Disciplinas\n");
	printf("\t(3)- Lançar Notas\n");
	printf("\t(4)- Editar Disciplina\n");
	printf("\t(5)- Cancelar Oferta de Disciplina\n");
	printf("--------------------------------------------------------------------\n");
	printf("\t(0)- Retornar ao MENU PRINCIPAL\n\n");
	printf("Opção: ");
	scanf(" %d", &opcao);
	
	return opcao;
}

void cadastrar_disciplina(FILE** arq) {
	system("clear");

	Disciplina nova;
	int encontrou_vaga = 0;

	printf("==============================================\n");
	printf("		Cadastro Disciplinas\n");
	printf("==============================================\n\n");

	rewind(arq[DISC]);
	while (fread(&nova, sizeof(Disciplina), 1, arq[DISC])) {
		if (nova.val == 0) {
			encontrou_vaga = 1;
			nova.cod_disciplina = nova.cod_disciplina; 
			fseek(arq[DISC], -sizeof(Disciplina), SEEK_CUR);
			break;
		}
	}

	if (!encontrou_vaga) {
		fseek(arq[DISC], 0, SEEK_END);
		int tam = ftell(arq[DISC]);
		nova.cod_disciplina = (tam / sizeof(Disciplina)) + 1;
	}

	nova.val = 1;

	printf("\nCódigo Disciplina: %d", nova.cod_disciplina);
	printf("\nNome: ");
	scanf(" %[^\n]s", nova.nome);
	printf("Carga Horária: ");
	scanf(" %d", &nova.ch);
	printf("Professor: ");
	scanf(" %[^\n]s", nova.professor);

	if (fwrite(&nova, sizeof(Disciplina), 1, arq[DISC])) {
		fflush(arq[DISC]);
		printf("\nDisciplina Cadastrada com Sucesso!\n");
	} else {
		printf("\nErro ao cadastrar disciplina!\n");
	}

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

int verificar_disciplina(FILE** arq) {
    Disciplina disciplina;
    
    printf("Digite o código da disciplina ((-1)- para sair): ");
    int cod_disciplina;
    scanf("%d", &cod_disciplina);
    
    if(cod_disciplina == -1)
		return -1;
    
    fseek(arq[DISC], 0, SEEK_SET);
    while(fread(&disciplina, sizeof(Disciplina), 1, arq[DISC])) 
        if(disciplina.cod_disciplina == cod_disciplina && disciplina.val == 1) 
            return disciplina.cod_disciplina;
        
    return 0;
}

void diario_disciplina(FILE** arq, Disciplina* disc, int id, int cod_disciplina) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Diário Disciplina\n");
	printf("==============================================\n\n");
	
	fseek(arq[DISC], 0, SEEK_END);
	int tam = ftell(arq[DISC]);
	if(!tam) {
		printf("Não há disciplinas cadastradas!\n");
		wait();
		return;
	}
	
	if (disc[id].val == 0) {
		printf("Disciplina cancelada.\n");
		wait();
		return;
	}
		
	printf("\nDisciplina:  %s\tCódigo: %d\tProfessor: %s\tCarga Horária: %d\n", disc[id].nome, disc[id].cod_disciplina, disc[id].professor, disc[id].ch);
	printf("Alunos Matriculados:\n\n");
				
	print_discente(arq, cod_disciplina);
}

void relatorio_disciplina(FILE** arq) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Relatório Disciplinas\n");
	printf("==============================================\n\n");
	
	fseek(arq[DISC], 0, SEEK_END);
	int tam = ftell(arq[DISC]);
	if(!tam) {
		printf("Não há disciplinas cadastradas!\n");
		wait();
		return;
	}
	
    Disciplina disc[100];
    int cont= 0;    
    int cod_disciplina;

    rewind(arq[DISC]);
    printf("Disciplinas Cadastradas:\n\n");
    while(fread(&disc[cont], sizeof(Disciplina), 1, arq[DISC]))
		if(disc[cont].val == 1)
			cont++;
        
    if(!cont) {
		printf("Nenhuma Disciplina Cadastrada!\n");
		wait();
		return;
	}
	
	ordem_bubble_sort(disc, cont);    
	
	for(int i=0; i<cont; i++) {
		printf("Código: %d | Nome: %s\n", disc[i].cod_disciplina, disc[i].nome);
		printf("----------------------------------------------------------------------\n");
	}	

    printf("\nDigite o código da disciplina para detalhes ((-1)- para sair)): ");
    scanf("%d", &cod_disciplina);
    
    if(cod_disciplina == -1) {
		printf("Saindo de RELATÓRIO DISCIPLINAS\n");
		wait();
		return;
	}
    
    int x= 0, id;
    for(int i=0; i<cont; i++)
		if(cod_disciplina == disc[i].cod_disciplina) {
			x = 1;
			id = i;
			break;
		}	
    
    if(x) 
		diario_disciplina(arq, disc, id, cod_disciplina);
	else {
		system("clear");
		printf("Disciplina não encontrada!\n");	
		wait();
	}
	
	return;
}

void lancar_nota(FILE** arq) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Lançar Notas\n");
	printf("==============================================\n\n");
	
	Matricula mat;
	
	int id_discente;
	do {
		id_discente = verificar_discente(arq);
		
		if(id_discente == -1) {
			printf("Nota Cancelada!\n");
			wait();
			return;
		}
		
		if(!id_discente) {
			printf("Discente não encontrado! Tente novamente..\n");
			wait();
			continue;
		}
		
		break;
	}while(1);
       
    int id_disciplina;		
	do{	
		id_disciplina = verificar_disciplina(arq);
		
		if(id_disciplina == -1) {
			printf("Nota Cancelada!\n");
			wait();
			return;
		}
		
		if(!id_disciplina) {
			printf("Disciplina não encontrada! Tente novamente..\n");
			wait();
			continue;
		}
		
		break;
	}while(1);
	
	float nota;
	rewind(arq[MAT]);
    while(fread(&mat, sizeof(Matricula), 1, arq[MAT]))
        if(mat.cod_discente == id_discente && mat.cod_disciplina == id_disciplina && mat.val == 1) {
            printf("Digite a nova nota: ");
            scanf(" %f", &nota);
            
            mat.notas = nota;
            
            fseek(arq[MAT], -sizeof(Matricula), SEEK_CUR);
            fwrite(&mat, sizeof(Matricula), 1, arq[MAT]);
            fflush(arq[MAT]);
            
            printf("Nota atualizada com sucesso!\n");
            wait();
            return;
        }

    printf("Matrícula não encontrada!\n");
    
    wait();
}

void edit_disciplina(FILE** arq) {
	system("clear");
	
	printf("==============================================\n");
	printf("		Editar Disciplina\n");
	printf("==============================================\n\n");
	
	fseek(arq[DISC], 0, SEEK_END);
	int tam = ftell(arq[DISC]);
	if(!tam) {
		printf("Não há disciplinas cadastradas!\n");
		wait();
		return;
	}
	
	Disciplina disc;
	int id;
	do {
		id = verificar_disciplina(arq);
		
		if(id == -1) {
			printf("Saindo..\n");
			wait();
			return;
		}
		
		if(!id) {
			printf("Disciplina não encontrada! Tente novamente..\n");
			wait();
			continue;
		}
		
		break;
	}while(1);
	
	rewind(arq[DISC]);
	while(fread(&disc, sizeof(Disciplina), 1, arq[DISC]))
		if(id == disc.cod_disciplina) {
			fseek(arq[DISC], -sizeof(Disciplina), SEEK_CUR);
			printf("Novo nome: ");
			scanf(" %[^\n]s", disc.nome);
			printf("Nova carga horária: ");
			scanf(" %d", &disc.ch);
			printf("Novo Professor: ");
			scanf(" %[^\n]s", disc.professor);
			
			fwrite(&disc, sizeof(Disciplina), 1, arq[DISC]);
			fflush(arq[DISC]);
			
			printf("Disciplina editada com Sucesso!\n");
			wait();
		}
}

void cancelar_disciplina(FILE** arq) {
	system("clear");

	printf("==============================================\n");
	printf("		Cancelar Disciplina\n");
	printf("==============================================\n\n");

	fseek(arq[DISC], 0, SEEK_END);
	int tam = ftell(arq[DISC]);
	if (!tam) {
		printf("Não há disciplinas cadastradas!\n");
		wait();
		return;
	}

	int id;
	do {
		id = verificar_disciplina(arq);

		if (id == -1) {
			printf("Cancelamento Abortado!\n");
			wait();
			return;
		}

		if (!id) {
			printf("Disciplina não encontrada! Tente novamente..\n");
			wait();
			continue;
		}

		break;
	} while (1);

	Disciplina disc;

	rewind(arq[DISC]);
	while (fread(&disc, sizeof(Disciplina), 1, arq[DISC])) {
		if (disc.cod_disciplina == id && disc.val == 1) {
			disc.val = 0;

			fseek(arq[DISC], -sizeof(Disciplina), SEEK_CUR);
			fwrite(&disc, sizeof(Disciplina), 1, arq[DISC]);
			fflush(arq[DISC]);

			printf("Disciplina cancelada com sucesso!\n");
			wait();
			return;
		}
	}

	printf("Erro: Disciplina já está cancelada ou não encontrada!\n");
	wait();
}

void controller_disciplina(FILE** arq){
	do{
		switch(menu_disciplina()){
			case 1:	
					cadastrar_disciplina(arq); 
					break;
					
			case 2: 
					relatorio_disciplina(arq);
					break;
					
			case 3: 
					lancar_nota(arq);
					break;
					
			case 4: 
					edit_disciplina(arq);
					break;		
						
			case 5: 
					cancelar_disciplina(arq);
					break;	
							
			case 0: return;		
			
			default: 
					printf("Opção Inválida! Tente novamente..\n");
					wait();
		}
	}while(1);
}
