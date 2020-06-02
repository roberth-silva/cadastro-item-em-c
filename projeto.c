#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>
#include<string.h>


typedef struct elemento{
    int id;
    char descricao[100];
    float valor;
    struct elemento *prox;
}Elemento;

Elemento* listaGeral; //lista geral de itens

//função para criar a lista: retorna uma lista vazia
Elemento* criar_lista(void){
    return NULL;
}

//Inserção no ínicio da lista
Elemento* inserir_no(Elemento* lista, int id, char descricao[], float valor){
    Elemento * no = (Elemento*)malloc(sizeof(Elemento));
    no -> id = id;
    strcpy(no -> descricao, descricao);
    no -> valor = valor;
    no -> prox = lista;
    return no;
}

void imprimir_lista(Elemento *lista){
    Elemento *p;//declarar ponteiro auxiliar p

    for(p = lista; p != NULL; p = p -> prox){
        printf("\nId: %d\n", p->id);
        printf("Item: %s", p->descricao);
        printf("Valor: %.2f\n", p->valor);
    }
}

int verificar_lista_vazia(Elemento *lista){
    if(lista == NULL){
        return 1;//retorna 1 se vazia e 0 senão
    }else{
        return 0;
    }
}

int novo_id(Elemento *lista){
    Elemento *p;//declarar ponteiro auxiliar p
    int maxId=0;
    for(p = lista; p != NULL; p = p -> prox){
        if(maxId < p->id)
            maxId = p->id;
    }
    return maxId;
}

int tamanho_lista(Elemento *lista){
    int i=0;
    Elemento *p;

    for(p = lista; p != NULL; p = p -> prox){
        i++;
    }
    return i;
}

void deleta_no(Elemento **primeiro_no, int id)
{
    Elemento* temp = *primeiro_no, *anterior;

    if (temp != NULL && temp->id == id)
    {
        *primeiro_no = temp->prox;
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != id)
    {
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL) return;

    anterior->prox = temp->prox;

    free(temp);

    return;
}

void salvar_no_arquivo(Elemento *lista){
    FILE *f;

    f = fopen("arquivo.txt","w+");

    Elemento *p;

    for(p = lista; p != NULL; p = p -> prox){
        fprintf(f,"%d\n", p->id);
        fprintf(f,"%s", p->descricao);
        fprintf(f,"%.2f\n", p->valor);
        fprintf(f,"@\n");
    }

    fclose(f);
}

void carregar_do_arquivo(){
    system("clear||cls");

    FILE *f;
    size_t len = 255;
    char *line = malloc(sizeof(char) * len);

    f = fopen("arquivo.txt","r");

    if (f == NULL){
        printf("Could not open file");
        return;
    }

    free(listaGeral);
    listaGeral = criar_lista();

    int aux=0;
    int id;
    char descricao[200];
    float valor;

    while (fgets(line, len, f) != NULL){
        if (!strcmp(line,"@\n")==0){
                if(aux==0)
                    //id = (int)*line;
                    id = atoi(line);
                else if(aux==1)
                    strcpy(descricao,line);
                else if(aux==2)
                    //valor = (float)*line;
                    valor = atof(line);
            aux++;
            //printf("%d %d %s %.2f\n",aux,id,descricao,valor);
        }else if(strcmp(line,"@\n")==0){
            aux=0;
            listaGeral = inserir_no(listaGeral, id, descricao, valor);
        }
    }

    free(line);
    fclose(f);
}


void cabecalho(){
    printf("********************************************************\n");
    printf("********************************************************\n");
    printf("SISTEMA TEMPLATE DE CONTROLE DE CADASTROS v0.1\n");
    printf("********************************************************\n");
    printf("********************************************************\n\n");
    printf("********************************************************\n");
    printf("FACULDADE PITÁGORAS - SÃO LUÍS\n");
    printf("CURSO: CIÊNCIA DA COMPUTAÇÃO\n");
    printf("AUTOR: PROF. MSc. ROBERTH SILVA\n");
    printf("********************************************************\n\n\n\n");
}

void rodape(){
    printf("\n\n\nCréditos: Prof. MSc. Roberth Silva - Todos os direitos reservados.\n");
    printf("                     roberth.silva@kroton.com.br\n");
}

void menuCadastro(){
    system("clear||cls");
    printf("********************************************************\n");
    printf("********************MENU CADASTRO***********************\n");
    printf("********************************************************\n\n");

    char op;

    do{
        system("clear||cls");
        printf("********************************************************\n");
        printf("********************MENU CADASTRO***********************\n");
        printf("********************************************************\n\n");

        int id;
        char descricao[100];
        float valor;

        if(verificar_lista_vazia(listaGeral))
            id = 1;
        else
            id = novo_id(listaGeral)+1;

        printf("\nDigite a descrição do item: ");
        fgets(descricao, sizeof descricao, stdin);

        printf("Digite o valor do item: ");
        scanf("%f",&valor);
        getchar();

        listaGeral = inserir_no(listaGeral,id,descricao,valor);

        system("clear||cls");
        printf("********************************************************\n");
        printf("********************MENU CADASTRO***********************\n");
        printf("********************************************************\n\n");
        imprimir_lista(listaGeral);

        printf("\nDeseja cadastrar um novo item? (s/n) ");
        scanf("%s", &op);
        getchar();

    }while(op=='s');

    menuPrincipal();
}

void menuListagem(){

    char op;

    do{
        system("clear||cls");
        printf("********************************************************\n");
        printf("********************MENU LISTAGEM***********************\n");
        printf("********************************************************\n\n");

        if(tamanho_lista(listaGeral) > 0){
            imprimir_lista(listaGeral);

        }else{
            printf("\nNão existem registros cadastrados.\n");
        }

        printf("\nDeseja voltar ao menu principal? (s/n) ");
        scanf("%s", &op);
        getchar();

    }while(op=='n');

    menuPrincipal();
}

void menuDetalhes(){
    char op;
    int id;
    int achou = 0;
    do{
        system("clear||cls");
        printf("********************************************************\n");
        printf("********************MENU DETALHES***********************\n");
        printf("********************************************************\n\n");

        printf("Digite o codigo do item: ");
        scanf("%d", &id);

        Elemento *p;
        for(p = listaGeral; p != NULL; p = p -> prox){
            if(p->id == id){
                printf("\nId: %d\n", p->id);
                printf("Item: %s", p->descricao);
                printf("Valor: %.2f\n", p->valor);
                achou = 1;
            }
        }
        if(!achou){
            printf("\n*********************************************");
            printf("\nNão foi encontrado nenhum item com o id %d.", id);
            printf("\n*********************************************\n");
        }

        printf("\nDeseja realizar outra busca? (s/n) ");
        scanf("%s", &op);
        getchar();

    }while(op=='s');

    menuPrincipal();
}

void menuEdicao(){
    char op;
    int id;
    int achou = 0;
    do{
        system("clear||cls");
        printf("********************************************************\n");
        printf("********************MENU EDIÇÃO*************************\n");
        printf("********************************************************\n\n");

        printf("Digite o codigo do item: ");
        scanf("%d", &id);

        Elemento *p;
        char descricao[100];
        float valor;

        for(p = listaGeral; p != NULL; p = p -> prox){
            if(p->id == id){
                achou = 1;

                printf("Digite o valor do item: ");
                scanf("%f",&valor);
                getchar();

                printf("\nDigite a descrição do item: ");
                fgets(descricao, sizeof descricao, stdin);

                strcpy(p->descricao, descricao);
                p->valor = valor;
            }
        }
        if(!achou){
            printf("\n*********************************************");
            printf("\nNão foi encontrado nenhum item com o id %d.", id);
            printf("\n*********************************************\n");
        }

        printf("\nDeseja realizar outra busca? (s/n) ");
        scanf("%s", &op);
        getchar();

    }while(op=='s');

    menuPrincipal();
}

void menuExclusao(){
    char op;
    int id;
    int achou = 0;
    do{
        system("clear||cls");
        printf("********************************************************\n");
        printf("********************MENU EXCLUSÃO***********************\n");
        printf("********************************************************\n\n");

        printf("Digite o codigo do item a ser EXCLUÍDO: ");
        scanf("%d", &id);

        Elemento *p;
        char descricao[100];
        float valor;
        int resultado=0;

        deleta_no(&listaGeral,id);

        if(tamanho_lista(listaGeral) > 0){
            printf("\nListagem de itens atualizada:\n");
            imprimir_lista(listaGeral);

        }else{
            printf("\nNão existem registros cadastrados.\n");
        }

        printf("\nDeseja realizar outra busca? (s/n) ");
        scanf("%s", &op);
        getchar();

    }while(op=='s');

    menuPrincipal();
}

void menuPrincipal(){
    int op;
    do{
        system("clear||cls");
        cabecalho();
        printf("********************************************************\n");
        printf("********************MENU PRINCIPAL**********************\n");
        printf("********************************************************\n\n");
        printf("---------------------------------------------------\n");
        printf("Escolha dentre as opções abaixo:\n");
        printf("---------------------------------------------------\n");
        printf("1 - CADASTRAR ITEM;\n");
        printf("2 - LISTAR ITENS;\n");
        printf("3 - DETALHAR ITEM;\n");
        printf("4 - ALTERAR ITEM;\n");
        printf("5 - EXCLUIR ITEM;\n");
        printf("6 - SALVAR ESTOQUE\n");
        printf("7 - CARREGAR ESTOQUE\n");
        printf("8 - SAIR DO SISTEMA\n");
        printf("---------------------------------------------------\n");

        scanf("%d", &op);
        getchar();

        switch(op){
            case 1:
                menuCadastro();
                break;
            case 2:
                menuListagem();
                break;
            case 3:
                menuDetalhes();
                break;
            case 4:
                menuEdicao();
                break;
            case 5:
                menuExclusao();
                break;
            case 6:
                salvar_no_arquivo(listaGeral);
                break;
            case 7:
                carregar_do_arquivo();
                break;
            case 8:
                exit(0);
        }

    }while(op!=8);
}

int main(void){
    setlocale(LC_ALL,"");
    listaGeral = criar_lista();
    menuPrincipal();
    rodape();
}
