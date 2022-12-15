#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <locale.h>

#include "headerGraficas.h"
#include "headerEstrutura.h"

void tela1(int xMax, int yMax){
    int index;
    int escolha, highlight=0;
    char escolhas[4][26]={"Inserir Participante", "Sortear", "Conferir quem e seu amigo", "Fechar o programa"};
    noecho();//O echo natural do prompt de comando é desligado para que o programa tenha mais controle sobre
    while(1){//o que está aparecendo na tela
        clear();
        mvprintw(0, (xMax/2)-6, "Amigo Secreto");
        mvprintw(16, (xMax/2)-30, "Use as setas para cima e para baixo para navegar entre as opções");
        mvprintw(18, (xMax/2)-25, "Pressione a Barra de Espaço para escolher uma opção");
        for(index=0; index<4; index++){
            if(index==highlight)
                wattron(stdscr, A_REVERSE);
            mvprintw(index+10, (xMax/2)-(sizeof(escolhas[index])/2), "%s", escolhas[index]);
            wattroff(stdscr, A_REVERSE);//Dentro desse for e if o programa desenha todas as opções na tela
        }                               //e destaca a opção atual, que muda com o switch case abaixo
        escolha = getch();

        switch(escolha){//Usa-se as setas do teclado para navegar as opções acima
            case 'A':
                highlight--;
                if(highlight==-1)
                    highlight = 0;
                break;
            case 'B':
                highlight++;
                if(highlight== 4)
                    highlight = 3;
                break;
            default:
                break;
        }
        if(escolha == 32){//Quando o usuário pressiona a barra de espaço a opção atual é escolhida e o programa
            if(highlight==0)//entra na tal opção
                tela2(xMax, yMax);
            if(highlight==1)//Essa opção realiza o sorteio
                sortear(&listaEntrada, &listaSaida);
            if(highlight==2)
                tela3(xMax,yMax);
            if(highlight==3){//Essa opção fecha o programa
                clear();
                endwin();
                exit(1);
            }
                
        }        
    }
    refresh();
}

void tela2(int xMax, int yMax){//Função ativada quando a primeira opção é escolhida. Ela permite que você insira
    char caractere, palavra[50]="";//um nome na lista de entrada
    WINDOW *win = newwin(3,50,13, (xMax/2)-25);
    int index;
    index = 0;
    clear();
    while(1){
        box(win, 0, 0);
        mvprintw(0, (xMax/2)-6, "Amigo Secreto");
        mvprintw(10, (xMax/2)-16, "Insira o nome do(a) participante:");
        mvprintw(17, (xMax/2)-13, "Pressione ENTER para inserir");
        mvprintw(20, (xMax/2)-12, "Pressione ESC para voltar");
        refresh();

        caractere = getchar();//O controle da entrada de dados é feito letra por letra para não permitir que o usuário digite outra coisa
        if((caractere >= 97 && caractere <= 122) || (caractere >= 65 && caractere <=90) || caractere == 32)
        {
            palavra[index] = caractere;
            index++;
            mvwprintw(win, 1, 1, "%s", palavra);
            wrefresh(win);//Toda vez que uma letra é recebida a janela de texto é recarregada para ter 
            wclear(win);  //a impressão que o que está sendo digitado está sendo escrito na tela 
        }
        if(caractere == 13 && palavra[0] != '\0')
        {//Quando ENTER é pressionado e a caixa de texto não está vazia, o que estiver lá será inserido na lista
            palavra[index]='\0';
            insere(&listaEntrada, palavra);
            mvprintw(yMax-2,(xMax/2)-12, "Adicionado: %s  ", palavra);
            while(index>=0)//E a string palavra é zerada novamente para ser reutilizada
            {
                palavra[index]='\0';
                index--;
            }
            mvwprintw(win, 1, 1, "%s", palavra);
            wrefresh(win);
            wclear(win);
            index=0;
        }
        if(caractere == 27){//Caso a tecla ESC for pressionada o programa volta para a tela principal
            delwin(win);
            return;
        }
    }
    nocbreak();
    refresh();
}

void tela3(int xMax, int yMax){//Quando a terceira opção na tela principal é escolhida essa função é chamada.
    char caractere, palavra[50]="";//Ela confere qual é o próximo nó de alguém específico, ou seja ela mostra
    WINDOW *win = newwin(3,50,13, (xMax/2)-25);// quem foi o amigo secreto que foi sorteado para a pessoa
    int index;                                 //Apenas uma checagem por vez é possível. Para checar outra
    struct no *aux;                            //pessoa tem que antes voltar para o menu principal e só então
    lista *l = &listaSaida;                    //consultar a função novamente
    aux = l->inicio->prox;
    index = 0;
    clear();
    while(1){
        box(win, 0, 0);
        mvprintw(0, (xMax/2)-6, "Amigo Secreto");
        mvprintw(10, (xMax/2)-16, "Insira o nome do(a) participante:");
        mvprintw(17, (xMax/2)-25, "Pressione ENTER para descobrir que é seu amigo secreto");
        mvprintw(20, (xMax/2)-12, "Pressione ESC para voltar");
        refresh();

        caractere = getchar();//o controle de entrada é feito igual o da função anterior
        if((caractere >= 97 && caractere <= 122) || (caractere >= 65 && caractere <=90) || caractere == 32)
        {
            palavra[index] = caractere;
            index++;
            mvwprintw(win, 1, 1, "%s", palavra);
            wrefresh(win);
            wclear(win);
        }
        if(caractere == 13 && palavra[0] != '\0')//Quando você escreve seu nome e pressiona ENTER esse 
        {                                        //if começa a procurar por seu nome na lista
            if(strcmp(l->inicio->nome, palavra)==0){//esse if confere se o seu nome é o primeiro
                mvprintw(yMax-2, (xMax/2)-12, "Seu amigo secreto é %s", l->inicio->prox->nome);
            }
            else if(strcmp(l->fim->nome, palavra)==0){//esse if confere se seu nome é o último
                mvprintw(yMax-2, (xMax/2)-12, "Seu amigo secreto é %s", l->fim->prox->nome);
            }
            else{//E caso seu nome esteja no meio da lista os códigos abaixo procuram por ele
                while(1){
                    if(aux==l->fim)
                        break;
                    if(strcmp(aux->nome, palavra)==0){
                        mvprintw(yMax-2, (xMax/2)-12, "Seu amigo secreto é %s", aux->prox->nome);
                        break; 
                    }
                    aux = aux->prox;
                }
            } 
        }
        if(caractere == 27)//Caso a tecla ESC seja pressionada o usuário volta para o menu principal
            return;
    }
}