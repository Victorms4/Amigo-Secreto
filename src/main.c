// Escrito por: Victor Marques de Souza
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "headerEstrutura.h"
#include "headerGraficas.h"

int main(void){
    int xMax, yMax;

    setlocale(LC_ALL, "Portuguese");
    cria(&listaEntrada);
    cria(&listaSaida);
    
    initscr();  //inicializa a biblioteca ncurses
    cbreak();   
    
    getmaxyx(stdscr, yMax, xMax); //recebe por referência quantas colunas e quantas linhas

    tela1(xMax, yMax); //chama a tela principal do programa

    endwin();  //fecha a ncurses para ter certeza que o prompt de comando voltará ao normal01
}