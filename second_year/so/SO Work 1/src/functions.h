//
//  functions.h
//  SO Work 1
//
//  Created by João on 23/03/2022.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct geral{
   struct work *data;
   int *states;                    // => Estados dos processos                      New - 1 | Ready - 2 | Running - 3 | Block - 4 | Exit - 5
   int *pos;                       // => Posição de cada processo no seu array
   int nprocesses;
   int running;                    // => processo que está no running      (Se não tiver nenhum = -1)
   struct QueueRecord *blocked;    // => processos no blocked
   struct QueueRecord *ready;      // => processos no ready
   int comp;
   int Quantum;                    // => Just our friendly neighborhood Quantum
    
};

struct work{
    int *p;                        // => Informações
    int beginRun;                   // => Instante em que começou o Run atual
    
};

struct geral processHandler(struct geral g, int instante);
struct geral processHandler2(struct geral g, int instante, int robin);

int Wlen(int **arr);

int Wlen2(int arr[][10]);

int Hlen(int **arr);

int Hlen2(int arr[][10]);

void freeMemory(struct work data);

#endif /* functions_h */
