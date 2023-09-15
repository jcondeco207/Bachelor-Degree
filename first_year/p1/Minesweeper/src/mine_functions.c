//__  __ _
//|  \/  (_)_ __   ___  _____      _____  ___ _ __   ___ _ __
//| |\/| | | '_ \ / _ \/ __\ \ /\ / / _ \/ _ \ '_ \ / _ \ '__|
//| |  | | | | | |  __/\__ \\ V  V /  __/  __/ |_) |  __/ |
//|_|  |_|_|_| |_|\___||___/ \_/\_/ \___|\___| .__/ \___|_|
//                                          |_|
//
//  mine_functions.c
//  Minesweeper
//
//  Created by João Condeço and Pedro Leitão on 20/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "mine_functions.h"
#include "time.h"
#include <ctype.h>
#include <math.h>


int artificial_round(float num)
{
    if(num<0){
        return num - 0.5;
    }
    else{
        return num + 0.5;
    }
}

//Recolhe as informações para gerar o tabuleiro
void data(){
    struct board d;
    int nlines = 0, ncols = 0, nmines = 0, dimensions = 0;
    float l, c;
    
    while (dimensions == 0) {
        printf("\n\nInsira, separado por espaços, o número de linhas, colunas e minas.\nPor exemplo: 10 15 5\nDados: ");
        scanf("%d %d %d", &nlines, &ncols, &nmines);
        
        if((ncols > 0 && ncols<=26) && (nlines > 0 && nlines <=26) && (nmines > 0 && nmines < (nlines * ncols))){
            dimensions = nlines;
        }
        else{
            printf("\nInsira um valor para as linhas e colunas válido\n");
        }
        
        l = (float)nlines;
        c = (float)ncols;
        float min = (l*c)/8;
        
        if (nmines < min) {
            dimensions = 0;
            printf("O número minimo de minas deverá ser igual ou superior a: %d", artificial_round(min));
        }
    }
    
    d.nlines = nlines;
    d.ncols = ncols;
    d.nmines = nmines;
    
    generate_board(d, nlines, ncols, nmines);
}

//verifica se uma coordenada já existe nos arrays à nossa escolha
int existe_no_array(int arr[], int arr2[], int tested, int tested2){
    int i = 0, t = 0;
    for(i=0; i<1676; i++){
        if(arr[i] == tested && arr2[i] == tested2 && (arr[i] != 0 && arr2[i]!=0)){
            t +=1;
            i = 1677;
        }
    }
    return t;
}

int acha_minas(struct board d, int row, int column){
     int mines = 0;
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row-1, column))
        mines++;
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row+1, column))
        mines++;
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row, column-1))
        mines++;
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row, column+1))
        mines++;
    
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row-1, column+1))
        mines++;
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row-1, column-1))
        mines++;
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row+1, column+1))
        mines++;
    if(existe_no_array(d.coordinates.x, d.coordinates.y, row+1, column-1))
        mines++;


    return mines;
}

struct board flag(struct board d, int x, int y){
    for(int i=0; i<(d.ncols*d.nlines);i++){
        if(d.coordinates2.x[i] == x && d.coordinates2.y[i] == y){
            d.nflags +=1;
            d.coordinates2.x[i]=0;
            d.coordinates2.y[i]=0;
            i = 27;
        }
    }
    return d;
    
}

//calcula quantas minas há à volta da coordenada em causa
int number(struct board d, int i, int j){
    int n = 0;
    
    for(int y = 2; y>=0; y--){
        for(int x = 0; x<3; x++){
            if(existe_no_array(d.coordinates.x, d.coordinates.y, i+y, j+x) && ((i+y) != 0) && ((x+j)!=0)){
                n+=1;
            }
        }
    }
    return n;
}



struct board uncover(struct board d, int x, int y, int counter){
    int minas = 0;
    
    //verifica se está dentro do tabuleiro e se não choca contra nenhuma mina/número
    if((x <= 0 || y <= 0 || y > d.ncols || x > d.nlines || existe_no_array(d.coordinates.x, d.coordinates.y, x, y)==1 || existe_no_array(d.coordinates3.x, d.coordinates3.y, x, y)==1) && counter > 1){
       return d;
    }
    
    else{
        counter += 1;
        //adiciona mais um ao número de jogadas
        d.nj +=1;
        
        //adiciona à estrutura a jogada
        if(counter >= 1){
            d.coordinates3.x[d.nj]=x;
            d.coordinates3.y[d.nj]=y;
        }
        
        minas = acha_minas(d, x, y);
        if (minas < 1){
                
                //cima
                if( x-1 > 0)
                    d = uncover(d,x-1,y, counter);
                    
                //cima+direita
                if( y+1 <= d.ncols && x-1 > 0)
                    d = uncover(d,x-1,y+1, counter);
                
                //direita
                if( y+1 <= d.ncols)
                    d = uncover(d,x,y+1, counter);
                
                //direita+baixo
                if( y+1 <= d.ncols && x+1 <= d.nlines)
                    d = uncover(d,x+1,y+1, counter);
                
                //baixo
                if( x+1 <= d.nlines)
                    d = uncover(d,x+1,y, counter);
                
                //esquerda+baixo
                if( y-1 > 0 && x+1 <= d.nlines)
                    d = uncover(d,x+1,y-1, counter);
                
                //esquerda
                if( y-1 > 0)
                    d = uncover(d,x,y-1, counter);
                
                //esquerda+cima
                if( y-1 > 0 && x-1 > 0)
                    d = uncover(d,x-1,y-1, counter);
            }
        return d;
    }
    return d;
}

//imprime o tabuleiro sempre que solicitada
void print_board(struct board d,int nlines,int ncols, int showmines){
    
    char helper;
    int nm = 0;
    
    printf("\n\n   ");
    for (int m = 0; m<d.ncols; m++){
        helper = m + 65;
        printf("%c ", helper);
    }
    printf("\n");
    
    for(int i = 0; i<d.nlines; i++){
        
        if(i<9){
            printf(" %d ", i+1);
        }
        else{
            printf("%d ", i+1);
        }

        for (int j=0; j<d.ncols; j++) {
            if(existe_no_array(d.coordinates.x,d.coordinates.y, i+1,j+1) && nm <= d.nmines && showmines == 1){
                nm += 1;
                printf("* ");
            }
            else if (existe_no_array(d.coordinates2.x, d.coordinates2.y, i+1, j+1)){
                printf("f ");
            }
            else if (existe_no_array(d.coordinates3.x, d.coordinates3.y, i+1, j+1)){
                if(number(d, i, j)>0){
                    printf("%d ",number(d, i, j));
                }
                else{
                    printf("  ");
                }
            }
            else{
                printf(". ");
            }
        }
        printf("\n");
    }
    
    printf("\n\n");
}

//só para imprimir o caracter que eu quero as vezes que eu precisar
void print_chars(int n, char c){
    for(int i = 0; i<n; i++){
        printf("%c", c);
    }
}

//mostra a mensagem de fim de jogo
void game_ended(int its_on){
    char space = (char)32;
    char dash = (char)45;
    
    if (its_on == 0) {
        print_chars(11, space);
        print_chars(9, dash);
        print_chars(11, space);
        printf("\n");
        print_chars(10, dash);
        printf("|GAME OVER|");
        print_chars(10, dash);
        printf("\n");
        print_chars(11, space);
        print_chars(9, dash);
        print_chars(11, space);
        printf("\n\n");
    }
    else{
        print_chars(26, space);
        print_chars(26, dash);
        printf("\n");
        print_chars(25, dash);
        printf("|Parabéns! Concluiu o jogo!|");
        print_chars(25, dash);
        printf("\n");
        print_chars(26, space);
        print_chars(26, dash);
        printf("\n\n");
        
        for(int i = 0; i<30; i++){
            printf("-");
        }
        
        printf("\n\n");
    }
}


int on_off(struct board d){
    int dory = 0;
    for(int i=1; i<d.nlines+1; i++){
        for(int j=1;j<d.ncols+1;j++){
            if((existe_no_array(d.coordinates3.x, d.coordinates3.y, j, i)==0)&&(existe_no_array(d.coordinates.x, d.coordinates.y, j, i)==0)){
                dory=1;
            }
        }
    }
    return dory;
}


//onde decorre o jogo, recebe as jogadas e adiciona-as à estrutura
void game(struct board d,int nlines,int ncols, int showmines){
    char space = (char)32;
    char dash = (char)45;
    
    int its_on = 1, its_on2 = 1, flags_left = d.nmines, error;
    d.nj = 0;
    int selected_line, selected_column;
    char letter_column, action;
    
    
    while (/*(d.nflags < d.nmines || arrays_iguais(d)==0) && */(its_on == 1) && (its_on2 == 1)) {
                
        printf("\n\n");
        print_chars(1, space);
        print_chars(55, dash);
        printf("\n");
        printf("| Número de minas: %d   Número de bandeiras restantes: %d |\n", d.nmines, flags_left);
        print_chars(1, space);
        print_chars(55, dash);
        
        print_board(d, nlines, ncols, showmines);
        printf("\n\nDefina a posição e ação pretendida: u(ncover) ou f(lag)\nPor exemplo: 1 A u\nA sua jogada: ");
        scanf("%d %c %c", &selected_line, &letter_column, &action);
        
        selected_column = (int)(toupper(letter_column)) - 64;
        action = tolower(action);
        
        if(action == ((char)117)){
            //adiciona o espaço às jogadas
            d.coordinates3.x[d.nj] = selected_line;
            d.coordinates3.y[d.nj] = selected_column;
            
            //verifica se o espaço selecionado são minas
            if(existe_no_array(d.coordinates.x, d.coordinates.y, selected_line, selected_column)){
                its_on = 0;
                printf("\n\nRebentou\n\n");
            }
            
            //senão aqui expande
            else{
                d = uncover(d, selected_line, selected_column, 0);
                its_on2 = on_off(d);
            }
            
            d.nj += 1;
        }
        
        //adiciona as bandeiras
        else if(action == ((char)102)){
            if(existe_no_array(d.coordinates2.x, d.coordinates2.y, selected_line, selected_column)){
                d = flag(d, selected_line, selected_column);
                flags_left +=1;
                
            }
            else if(flags_left>0){
                d.coordinates2.x[d.nj] = selected_line;
                d.coordinates2.y[d.nj] = selected_column;
                //nj = uncover(d, nlines, ncols, selected_line, selected_column, nj);
                
                flags_left -= 1;
                d.nflags += 1;
            }
            d.nj += 1;
        }
        
        //para as jogadas inválidas
        else{
            printf("\nJogada inválida! Tente novamente.\n\n");
        }
    }
    
    showmines = 1;
    print_board(d, nlines, ncols, showmines);
    game_ended(its_on);
}

//adiciona as caracteristicas do tabuleiro à struct
void generate_board(struct board d, int nlines, int ncols, int nmines){
    
    char mineline, minecolune;
    char mine;
    int showmines = 0, ncolune;
    srand(time(NULL));
    
    for(int i = 0; i < nmines; i++){
        
        mineline = rand()% ((nlines)-1)+1;
        ncolune = (rand()% ((ncols)-1)+1) + 64;
        minecolune = ncolune;

        //estrutura para evitar minas repetidas
        if(existe_no_array(d.coordinates.x, d.coordinates.y, mineline, ncolune) && i>0){
            i-=1;
        }
        else{
            d.coordinates.y[i] = minecolune - 64;
            d.coordinates.x[i] = mineline;
            mine = (char)minecolune;
        }
    }
    
    game(d, nlines, ncols, showmines);
}

struct board receiver(){
    struct board d;
    char this_is_the_way[1200];
    int count = 0;
    
    printf("\nInsira o caminho para o ficheiro: ");
    scanf("%s", this_is_the_way);
    
    FILE *myf;

    myf = fopen(this_is_the_way, "r");
    if (myf == NULL) {
        
        printf("\nFicheiro indisponível.\n\n");
        exit(1);
    }
    else{
        char line;
        int y;
        
        fscanf(myf, "%d %d %d",&d.nlines,&d.ncols,&d.nmines);
        
        
        printf("lines = %d cols = %d", d.nlines, d.ncols);
        while(1){
            count +=1;
            if(fscanf(myf, "%d %c",&d.coordinates.x[count], &line)==EOF) break;
            y = ((int)line)-64;
            d.coordinates.y[count]=y;
        }
   }
    return d;
        
}
