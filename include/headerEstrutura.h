struct no
{
    char nome[50];
    struct no *prox;
};//Escolhi por usar uma lista simplesemente encadeada circular, por isso meu nó só tem um ponteiro de prox

typedef struct
{
    struct no *inicio;
    struct no *fim;
} lista;

lista listaEntrada, listaSaida;

void cria(lista *q);
int  insere(lista *q, char d[]);
int  retira(lista *q, char d[]);
void mostra(lista *q);
void sortear(lista *e, lista *s);