//
//  mine_functions.h
//  Minesweeper
//
//  Created by João on 02/01/2021.
//

#ifndef mine_functions_h
#define mine_functions_h

#include <stdio.h>

struct mines{
    int x[1676];
    int y[1676];
};

struct flags{
    int x[1676];
    int y[1676];
};

struct selected{
    int x[1676];
    int y[1676];
};

struct board{
    int nmines;
    int nflags;
    int nlines;
    int ncols;
    int nj;
    //coordenadas das minas
    struct mines coordinates;
    //coordenadas das bandeiras
    struct flags coordinates2;
    //coordenadas das jogadas
    struct selected coordinates3;
};

void srand(unsigned int s);


//Recolhe os dados
void data(void);

//introduzir determinados caracteres
void print_chars(int n, char c);

//recolhe os dados, gera as minas e adiciona-os à estrutura
void generate_board(struct board d, int nlines, int ncols, int nmines);

//imprime o tabuleiro quando solicitado
void print_board(struct board d,int nlines,int ncols, int showmines);

//onde decorre o jogo
void game(struct board d, int nlines,int ncols, int showmines);

//
struct board uncover(struct board d, int x, int y, int counter);
//
struct board flag(struct board d, int x, int y);

//
struct board receiver(void);

//Mostra a mensagem de fim de jogo
void game_ended(int its_on);

#endif /* mine_functions_h */

