//
//  main.c
//  SO Work 1
//
//  Created by João on 23/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"



void printTitle(int nprocesses){
    printf("\033[0;33m\n           \n           ____                                _   _                 _ _\n          |  _ \\ _ __ ___   ___ ___  ___ ___  | | | | __ _ _ __   __| | | ___ _ __\n          | |_) | '__/ _ \\ / __/ _ \\/ __/ __| | |_| |/ _` | '_ \\ / _` | |/ _ \\ '__|\n          |  __/| | | (_) | (_|  __/|__ |__ \\ |  _  | (_| | | | | (_| | |  __/ |\n          |_|   |_|  \\___/ \\___\\___||___/___/ |_| |_|\\__,_|_| |_|\\__,_|_|\\___|_|\033[0m\n\n");
    
    
    
    printf("Instante | ");
    for (int i = 0; i < nprocesses; i++) {
        printf("proc%d | ", i+1);
    }
    printf("\n\n");
}
void printState(int n){
    if(n == 1){
        printf("NEW   ");
    }
    else if(n == 2){
        printf("READY ");
    }
    else if(n == 3){
        printf("RUN   ");
    }
    else if(n == 4){
        printf("BLCK  ");
    }
    else if(n == 6){
        printf("EXIT  ");
    }
    else{
        printf("      ");
    }
}

void printOutput(int instante, int nprocesses, int states[]){
    if(instante >= 9) printf("\033[0;33m%d\033[0m \t  ", (instante+1));
    else printf("\033[0;33m%d\033[0m  \t  ", (instante+1));

    for(int i = 0; i < nprocesses; i++){
        printf(" ");
        printState(states[i]);
    }
    printf("\n\n");
}

int endgame(int states[], int nprocesses){
    for(int i = 0; i < nprocesses; i++){
        if(states[i] != 0) return 1;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    int programas[3][10] = {{0,3,1,2,2,4,0,0,0,0},
                            {1,4,2,4,1,1,0,0,0,0},
                            {3,2,1,6,1,3,1,1,0,0}
    };
    
    int isRobin = 1; 
    struct geral g;
    g.Quantum = 3;
    g.nprocesses = *(&programas + 1) - programas;
    g.comp = sizeof(programas[0]) / sizeof(int);
    printf("%d", g.nprocesses);
    g.data = malloc((g.nprocesses + 2)*sizeof(g.data));
    g.states = (int*)calloc(g.comp, sizeof(int));
    g.pos = (int*)calloc(g.comp, sizeof(int));
    
    Queue b = CreateQueue(g.nprocesses);
    Queue r = CreateQueue(g.nprocesses);
    g.ready = r;
    g.blocked = b;
    MakeEmpty(g.ready);
    MakeEmpty(g.blocked);
    g.running = -1;
    
    for(int i = 0; i < g.nprocesses; i++){
       g.data[i].p = (int*)calloc((g.comp + 1), sizeof(int)); 
    }

    for(int i = 0; i < g.nprocesses; i++){
        for(int j = 0; j < g.comp; j++){
            g.data[i].p[j] = programas[i][j];
        }
    }

    printTitle(g.nprocesses);
    int instante = 0;
    g = processHandler2(g,instante, isRobin);
    printOutput(instante, g.nprocesses, g.states);

    instante++;
    
    
    while(1){
        g = processHandler2(g, instante, isRobin);
        printOutput(instante, g.nprocesses, g.states);
        instante++;
        if(!endgame(g.states, g.nprocesses)) break;
    }
    
    
    return 0;
}
