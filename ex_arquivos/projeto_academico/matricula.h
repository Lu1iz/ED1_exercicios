typedef struct {
    int cod_discente;
    float notas;
    int cod_disciplina;
    int val; 
} Matricula;

void wait();
int verificar_disciplina(FILE** arq);
int verificar_discente(FILE** arq);
void print_matricula(FILE** arq);

int menu_matricula() {
    system("clear");
    
    int opcao;
    
    printf("--------------------------------------------------------------------\n");
    printf("\t\t\tSistema MATRICULA\n");
    printf("--------------------------------------------------------------------\n\n");
    
    printf("COMANDOS: \n");
    printf("\t(1)- Realizar Matricula\n");
    printf("\t(2)- Consultar Todas Matriculas\n");
    printf("\t(3)- Cancelar Matricula\n");
    printf("--------------------------------------------------------------------\n");
    printf("\t(0)- Retornar ao MENU PRINCIPAL\n\n");
    printf("Opção: ");
    scanf(" %d", &opcao);
    
    return opcao;
}

void matricular_discente(FILE** arq) {
    system("clear");
    
    printf("==============================================\n");
    printf("\t\tMatriculas\n");
    printf("==============================================\n\n");
    
    Matricula nova;
    int id_discente;
    
    do {
        id_discente = verificar_discente(arq);
        
        if (id_discente == -1) {
            printf("Matricula Cancelada!\n");
            wait();
            return;
        }
        
        if (!id_discente) {
            printf("Discente não encontrado! Tente novamente..\n");
            wait();
            continue;
        }
        
        break;
    } while (1);
    
    int id_disciplina;
    do {    
        id_disciplina = verificar_disciplina(arq);
        
        if (!id_disciplina) {
            printf("Disciplina não encontrada! Tente novamente..\n");
            wait();
            continue;
        }
        
        break;
    } while (1);
    
    fseek(arq[MAT], 0, SEEK_SET);
    while (fread(&nova, sizeof(Matricula), 1, arq[MAT])) {
        if (nova.cod_discente == id_discente && nova.cod_disciplina == id_disciplina) {
            if (nova.val == 0) { 
                nova.val = 1;
                fseek(arq[MAT], -sizeof(Matricula), SEEK_CUR);
                fwrite(&nova, sizeof(Matricula), 1, arq[MAT]);
                fflush(arq[MAT]);
                printf("Matricula reativada com sucesso!\n");
                wait();
                return;
            } else {
                printf("Matricula já realizada!\n");
                wait();
                return;
            }
        }
    }
    
    nova.cod_discente = id_discente;
    nova.cod_disciplina = id_disciplina;
    nova.notas = 0;
    nova.val = 1;
    
    fseek(arq[MAT], 0, SEEK_END);
    fwrite(&nova, sizeof(Matricula), 1, arq[MAT]);
    fflush(arq[MAT]);
    printf("\nMatricula realizada com sucesso!\n");
    
    wait();
}

void consultar_matriculas(FILE** arq) {
    system("clear");
    
    printf("==============================================\n");
    printf("\t\tConsulta Matriculas\n");
    printf("==============================================\n\n");
    
    print_matricula(arq);
    
    wait();
}

void cancelar_matricula(FILE** arq) {
    system("clear");
    
    printf("==============================================\n");
    printf("\t\tCancelar Matricula\n");
    printf("==============================================\n\n");
    
    Matricula mat;
    int id_discente;
    int id_disciplina;
    
	 do {
        id_discente = verificar_discente(arq);
        
        if (id_discente == -1) {
            printf("Cancelamento Cancelado!\n");
            wait();
            return;
        }
        
        if (!id_discente) {
            printf("Discente não encontrado! Tente novamente..\n");
            wait();
            continue;
        }
        
        break;
    } while (1);
    
    do {    
        id_disciplina = verificar_disciplina(arq);
        
        if (!id_disciplina) {
            printf("Disciplina não encontrada! Tente novamente..\n");
            wait();
            continue;
        }
        
        break;
    } while (1);
    
    rewind(arq[MAT]);
    while (fread(&mat, sizeof(Matricula), 1, arq[MAT])) {
        if (mat.cod_discente == id_discente && mat.cod_disciplina == id_disciplina && mat.val == 1) {
            mat.val = 0; 
            fseek(arq[MAT], -sizeof(Matricula), SEEK_CUR);
            fwrite(&mat, sizeof(Matricula), 1, arq[MAT]);
            fflush(arq[MAT]);
            printf("Matricula cancelada com sucesso!\n");
            wait();
            return;
        }
    }
    printf("Matricula não encontrada ou já cancelada!\n");
    wait();
}

void controller_matricula(FILE** arq) {
    do {
        switch (menu_matricula()) {
            case 1:    
                matricular_discente(arq); 
                break;
                
            case 2: 
                consultar_matriculas(arq);
                break;
                
            case 3: 
                cancelar_matricula(arq);
                break;
                        
            case 0: return;        
            
            default: 
                printf("Opção Inválida! Tente novamente..\n");
                wait();
        }
    } while (1);
}
