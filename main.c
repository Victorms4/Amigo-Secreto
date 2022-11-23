#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <ctype.h>

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
int  insereSimples(lista *q, char d[50]);
int  insereCircular(lista *q, char d[50]);
int  retiraSimples(lista *q, char d[50]);
void mostraSimples(lista *q);

lista listaEntrada, listaSaida;
int ordem=0;
char caractere, palavra[50]="";

int main(void){
    int index;

    initscr();
    cbreak();
    //Comandos presentas na lncurses que permite que a saída padrão recebe os valores char sem
    //qu o usuário pressione a tecla ENTER no teclado
    cria(&listaEntrada);
    cria(&listaSaida);

    while(caractere != 13){
        caractere = tolower(getchar());
        if((caractere >= 97 && caractere <= 122) || caractere == 13)
        {
            palavra[index] = caractere;
            index++;
        }
        if(caractere == 32)
        {
            palavra[index]='\0';
            insereSimples(&listaEntrada, palavra);
            while(index>=0)
            {
                palavra[index]='\0';
                index--;
            }
            index=0;
        }
    }

    mostraSimples(&listaEntrada);
    retiraSimples(&listaEntrada, listaEntrada.inicio->nome);
    nocbreak();
}


void cria(lista *q)
{
    q->inicio = NULL;
    q->fim = NULL;
}

int  insereSimples(lista *q, char d[50])
{
    struct no *aux;
    aux = (struct no*) malloc(sizeof(struct no));
    if (aux == NULL)
        return 0;
    //Caso o malloc dê errado retorne 0
    if (q->inicio == NULL)
    {
        strcpy(aux->nome, d);
        q->inicio = aux;
        q->fim = aux;
        return 1;
    }
    //Esse if checa se o nó adicionado será o primeiro e trata esse caso especial
    strcpy(aux->nome, d);
    q->fim->prox = aux;
    aux->prox = NULL;
    q->fim = aux;
    return 1;
    //Todos os outro nós adicionados caem nesse caso
}

int  insereCircular(lista *q, char d[50])
{
    struct no *aux;
    aux = (struct no*) malloc(sizeof(struct no));
    if (aux == NULL)
        return 0;
    //Caso o malloc dê errado retorne 0
    if (q->inicio == NULL)
    {
        strcpy(aux->nome, d);
        q->inicio = aux;
        q->fim = aux;
        aux->prox = aux;
        return 1;
    }
    //Esse if checa se o nó adicionado será o primeiro e trata esse caso especial
    strcpy(aux->nome, d);
    q->fim->prox = aux;
    aux->prox = q->inicio;
    q->fim = aux;
    return 1;
    //Todos os outro nós adicionados caem nesse caso
}

void mostraSimples(lista *q)
{
    struct no *aux;
    aux=q->inicio;
    while(aux!=NULL)
    {
        printf("%s ", aux->nome);
        aux = aux->prox;
    }
}

int retiraSimples(lista *q, char string[])
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