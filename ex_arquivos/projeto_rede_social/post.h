typedef struct {
    int id;
    char username[50];
    char conteudo[50];
    int val;
} Post;

void wait();

void new_post(FILE** arq, char* username) {
    system("clear");

    printf("--------------------------------------------------------------\n");
    printf("\t\t\tNovo Post\n");
    printf("--------------------------------------------------------------\n\n");

    Post post;
    int achou = 0;

    Post temp;
    rewind(arq[POST]);
    while (fread(&temp, sizeof(Post), 1, arq[POST])) {
        if (temp.val == 0) {
            achou = 1;
            fseek(arq[POST], -sizeof(Post), SEEK_CUR);
            break;
        }
    }

    strcpy(post.username, username);
    post.val = 1;
    post.id = rand() % 1001;

    printf("Conteudo: ");
    scanf(" %[^\n]s", post.conteudo);

    if (!achou)
        fseek(arq[POST], 0, SEEK_END);

    if (fwrite(&post, sizeof(Post), 1, arq[POST])) {
        fflush(arq[POST]);
        printf("\nPost publicado com Sucesso!\n");
    }

    wait();
}

void all_post(FILE** arq, char* username) {
    system("clear");

    printf("--------------------------------------------------------------\n");
    printf("\t\t\tTodos Posts\n");
    printf("--------------------------------------------------------------\n\n");

    Post post;
    rewind(arq[POST]);

    printf("\tUser: %s\n\n", username);
    while (fread(&post, sizeof(Post), 1, arq[POST])) {
        if (post.val == 1 && strcmp(post.username, username) == 0) {
            printf("%s | Id: %d\n", post.conteudo, post.id);
            printf("========================================\n\n");
        }
    }

    wait();
}

void delete_post(FILE** arq, char* username) {
    system("clear");

    printf("--------------------------------------------------------------\n");
    printf("\t\t\tDeletar Post\n");
    printf("--------------------------------------------------------------\n\n");

    Post post;
    int id, achou = 0;

    printf("Informe o id do post para excluir: ");
    scanf(" %d", &id);

    rewind(arq[POST]);
    while (fread(&post, sizeof(Post), 1, arq[POST])) {
        if (post.id == id && strcmp(post.username, username) == 0 && post.val == 1) {
            achou = 1;
            post.val = 0;

            fseek(arq[POST], -sizeof(Post), SEEK_CUR);
            fwrite(&post, sizeof(Post), 1, arq[POST]);
            fflush(arq[POST]);

            printf("\nPost excluido com Sucesso!\n");
            break;
        }
    }

    if (!achou)
        printf("\nId não reconhecido ou você não tem permissão!\n");

    wait();
}
