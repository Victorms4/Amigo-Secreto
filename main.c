#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>

struct no
{
    char nome[50];
    struct no *prox;
};

typedef struct
{
    struct no *inicio;
    struct no *fim;
} lista;

void cria(lista *q);
int  insere(lista *q, char d[]);
int  retira(lista *q, char d[]);
void mostra(lista *q);
void sortear(lista *e, lista *s);

lista listaEntrada, listaSaida;
int nos=0;
char caractere, palavra[50]="";

int main(void){
    int index=0;

    initscr();
    cbreak();
    //Comandos presentas na lncurses que permite que a saída padrão recebe os valores char sem
    //qu o usuário pressione a tecla ENTER no teclado
    cria(&listaEntrada);
    cria(&listaSaida);

    while(caractere != 27){
        caractere = 0;
        while(caractere != 13 && caractere != 27){
            caractere = getchar();
            if((caractere >= 97 && caractere <= 122) || (caractere >= 65 && caractere <=90) || caractere == 32)
            {
                palavra[index] = caractere;
                index++;
            }
            if(caractere == 13 && palavra[0] != 0)
            {
                palavra[index]='\0';
                insere(&listaEntrada, palavra);
                printf("\nAdicionado: %s\n", palavra);
                while(index>=0)
                {
                    palavra[index]='\0';
                    index--;
                }
                index=0;
            }
        }
    }
    nocbreak();

    printf("%d nos\n", nos);
    mostra(&listaEntrada);
    printf("lista de entrada\n");

    sortear(&listaEntrada, &listaSaida);
    mostra(&listaSaida);
    printf("lista de saida\n");
    mostra(&listaEntrada);

    endwin();
}


void cria(lista *q)
{
    q->inicio = NULL;
    q->fim = NULL;
}


int  insere(lista *q, char d[])
{
    struct no *aux;
    aux = (struct no*) malloc(sizeof(struct no));
    if (aux == NULL)
        return 0;
    //Caso o malloc dê errado retorne 0
    if (q->inicio == NULL && q->fim == NULL)
    {
        strcpy(aux->nome, d);
        q->inicio = aux;
        q->fim = aux;
        aux->prox = aux;
        nos++;
        return 1;
    }
    //Esse if checa se o nó adicionado será o primeiro e trata esse caso especial
    strcpy(aux->nome, d);
    q->fim->prox = aux;
    aux->prox = q->inicio;
    q->fim = aux;
    nos++;
    return 1;
    //Todos os outro nós adicionados caem nesse caso
}

void mostra(lista *q)
{
    struct no *aux;
    aux=q->inicio;
    if(q->inicio == NULL)
        printf("\nlista vazia\n");
    if(q->inicio == q->fim)
    {
        printf("%s ", aux->nome);
        return;
    }
    do{
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }while(aux != q->inicio);
}

int retira(lista *q, char string[])
{
    struct no *aux, *anterior, *atual;
    if (q->inicio == NULL)
        return 0;
    //O primeiro if confere se a lista não está vazia
    if (q->inicio == q->fim && strcmp(string, q->inicio->nome) == 0)
    {
        aux = q->inicio;
        q->inicio = NULL;
        q->fim = NULL;
        free(aux);
        return 1;
    }
    //O segundo if confere se a lista tem apenas um nó
    if (q->inicio != q->fim && strcmp(string, q->inicio->nome) == 0)
    {
        aux = q->inicio;
        q->fim->prox = q->inicio->prox;
        q->inicio = q->inicio->prox;
        free(aux);
        return 1;
    }
    //O terceiro if confere se o nó desejado é o primeiro
    if (strcmp(string, q->fim->nome) == 0)
    {
        aux = q->inicio;
        while(aux->prox != q->fim){
            aux = aux->prox;
        }
        q->fim = aux;
        q->fim->prox = q->inicio;
        aux = aux->prox;
        free(aux);
        return 1;
    }
    //O quarto if confere se o nó desejado é o último

    anterior = q->inicio;
    atual = q->inicio->prox;
    while (atual != NULL && strcmp(string, atual->nome) != 0)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL)
    {
        return 0;
    }
    aux = atual;
    anterior->prox = atual->prox;
    free(aux);
    return 1;
    //Todos os outros casos caem nesse pedaço de código
}

void sortear(lista *e, lista *s){
    int sorteado, total=nos;
    struct no *aux;
    srand(time(NULL));
    while(total > 0){
        aux = e->inicio;
        sorteado = rand()%total;
        while(sorteado > 0){
            aux = aux->prox;
            sorteado--;
        }
        insere(s, aux->nome);
        retira(e, aux->nome);
        total--;
    }
    
}