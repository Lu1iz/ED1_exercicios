typedef struct {
    char username[50];
    char name[50];
    int senha;
} User;

void wait();
void new_post(FILE** arq, char* username);
void all_post(FILE** arq, char* username);
void delete_post(FILE** arq, char* username);

void new_user(FILE** arq) {
    User user, novo;
    int val;

    do {
        val = 1;
        system("clear");

        printf("--------------------------------------------------------------\n");
        printf("\t\t\tNOVO USER\n");
        printf("--------------------------------------------------------------\n\n");

        printf("Name: ");
        scanf(" %[^\n]s", novo.name);
        printf("UserName: ");
        scanf(" %s", novo.username);
        printf("Password (apenas números): ");
        scanf(" %d", &novo.senha);

        rewind(arq[USER]);
        while (fread(&user, sizeof(User), 1, arq[USER])) {
            if ((novo.senha == user.senha) || (!strcmp(novo.username, user.username))) {
                printf("\n\nUser ou senha já cadastrados!\nTente novamente..\n");
                val = 0;
                wait();
            }
        }

        if (val)
            break;
    } while (1);

    fseek(arq[USER], 0, SEEK_END);
    if (fwrite(&novo, sizeof(User), 1, arq[USER])) {
        fflush(arq[USER]);
        printf("\n\nUSER Cadastrado!\n");
    }

    wait();
}

int login(FILE** arq, char* logged_username) {
    system("clear");

    printf("--------------------------------------------------------------\n");
    printf("\t\t\tLOGIN\n");
    printf("--------------------------------------------------------------\n\n");

    fseek(arq[USER], 0, SEEK_END);
    int tam = ftell(arq[USER]);
    if (!tam) {
        printf("Não há usuários cadastrados!\n");
        wait();
        return 0;
    }

    User user;
    char u_name[50];
    int senha;

    printf("Username: ");
    scanf(" %s", u_name);
    printf("Senha: ");
    scanf(" %d", &senha);

    rewind(arq[USER]);
    while (fread(&user, sizeof(User), 1, arq[USER])) {
        if ((!strcmp(u_name, user.username)) && (senha == user.senha)) {
            strcpy(logged_username, user.username);
            return 1;
        }
    }

    printf("\n\nLogin Inválido\n");
    wait();

    return 0;
}

int menu_user(FILE** arq, char* username) {
    system("clear");

    User user;

    rewind(arq[USER]);
    while (fread(&user, sizeof(User), 1, arq[USER])) {
        if (strcmp(user.username, username) == 0) {
            printf("\t\tSeja Bem Vindo(a) <<< %s >>>\n\n", user.name);
            break;
        }
    }

    printf("(4)- Novo Post\n");
    printf("(5)- Listar Todos os Posts\n");
    printf("(6)- Excluir Post\n");
    printf("(7)- Alterar Senha\n");
    printf("(8)- Logout\n");

    int o;
    scanf(" %d", &o);

    return o;
}

void edit_senha(FILE** arq, char* username) {
    system("clear");

    User user;

    fseek(arq[USER], 0, SEEK_END);
    int tam = ftell(arq[USER]);
    if (!tam) {
        printf("Não há usuários cadastrados!\n");
        wait();
        return;
    }

    printf("--------------------------------------------------------------\n");
    printf("\t\t\tEditar Senha\n");
    printf("--------------------------------------------------------------\n\n");

    rewind(arq[USER]);
    while (fread(&user, sizeof(User), 1, arq[USER])) {
        if (strcmp(user.username, username) == 0) {
            fseek(arq[USER], -sizeof(User), SEEK_CUR);
            printf("Nova Senha: ");
            scanf(" %d", &user.senha);
            fwrite(&user, sizeof(User), 1, arq[USER]);
            fflush(arq[USER]);
            printf("Senha alterada com Sucesso!\n");
            break;
        }
    }

    wait();
}

void controller_user(FILE** arq) {
    char logged_username[50];

    if (login(arq, logged_username)) {
        do {
            switch (menu_user(arq, logged_username)) {
                case 4:
                    new_post(arq, logged_username);
                    break;

                case 5:
                    all_post(arq, logged_username);
                    break;

                case 6:
                    delete_post(arq, logged_username);
                    break;

                case 7:
                    edit_senha(arq, logged_username);
                    break;

                case 8:
                    return;

                default:
                    printf("Opção Inválida! Tente novamente...\n");
                    wait();
            }
        } while (1);
    }
}
