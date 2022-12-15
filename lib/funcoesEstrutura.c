#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "headerEstrutura.h"

int nos=0;

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
        return 0;//Caso o malloc dê errado retorne 0
    if (q->inicio == NULL && q->fim == NULL) //Esse if checa se o nó adicionado será o primeiro e trata esse caso especial
    {
        strcpy(aux->nome, d);
        q->inicio = aux;
        q->fim = aux;
        aux->prox = aux;
        nos++;
        return 1;
    }
    strcpy(aux->nome, d);//Todos os outro nós adicionados caem nesse caso
    q->fim->prox = aux;
    aux->prox = q->inicio;
    q->fim = aux;
    nos++;
    return 1;
}

void mostra(lista *q)//Essa é uma função que não é chamada na versão final do cósigo, porém usei muito dela para depurar o código e achar erros
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
        printf("%s  ", aux->nome);
        aux = aux->prox;
    }while(aux != q->inicio);
}

int retira(lista *q, char string[])
{
    struct no *aux, *anterior, *atual;
    if (q->inicio == NULL)//O primeiro if confere se a lista não está vazia
        return 0;
    if (q->inicio == q->fim && strcmp(string, q->inicio->nome) == 0)//O segundo if confere se a lista tem apenas um nó
    {
        aux = q->inicio;
        q->inicio = NULL;
        q->fim = NULL;
        free(aux);
        return 1;
    }
    if (q->inicio != q->fim && strcmp(string, q->inicio->nome) == 0)//O terceiro if confere se o nó desejado é o primeiro
    {
        aux = q->inicio;
        q->fim->prox = q->inicio->prox;
        q->inicio = q->inicio->prox;
        free(aux);
        return 1;
    }
    
    if (strcmp(string, q->fim->nome) == 0)//O quarto if confere se o nó desejado é o último
    {
        aux = q->inicio;
        while(aux->prox != q->fim){
            aux = aux->prox;
        }
        free(q->fim);
        aux->prox = q->inicio;
        q->fim = aux;
        return 1;
    }
    

    anterior = q->inicio;//Todos os outros casos caem nesse pedaço de código
    atual = q->inicio->prox;
    while (atual != q->inicio && strcmp(string, atual->nome) != 0)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == q->inicio)
    {
        return 0;
    }
    aux = atual;
    anterior->prox = atual->prox;
    free(aux);
    return 1;
}

void sortear(lista *e, lista *s){//A função sorteia um número, anda até o nó de tal número da lista de entrada, 
    int sorteado, i, total=nos; //insere na lista de saída e remove da lista de entrada
    struct no *aux;
    srand(time(NULL));
    while(total > 0){
        aux = e->inicio;
        sorteado = rand()%total;
        i=0;
        while(sorteado > i){
            aux = aux->prox;
            i++;
        }
        insere(s, aux->nome);
        retira(e, aux->nome);
        total--;
    }
    return;
}