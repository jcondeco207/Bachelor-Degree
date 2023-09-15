//------------------------------------------------------------------------------------//
// Trabalho de S.O.(Simulador de Sistema Operativo com Modelo de 5 Estados com threads e
// Gestão de Memória por segmentação)

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566), João Condeço (nº 48976) e João Oliveira (nº 48979)
// Junho de 2022
//-----------------------------------------------------------------------------------//


#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct SO{
    int mem[200];
    int params[200];
    int storage[200];
    int pos;
    int whoIsRunning;
    int quantum;
    int lastID;
    int instsAlocated;
    
    struct QueueRecord *ready;
    struct QueueRecord *blocked;
    List joinBlocked;
};

struct PCB{
    struct QueueRecord *code;
    struct QueueRecord *var;
    int loadTime;               // => Instante em que começa
    int ninsts;                 // => Nº de instruções 
    int ninsts_thread;          // => Nº de instruções na Thread
    int maxVar;                 // => Variável máxima 
    int maxVarThread;           // => Variável máxima das threads
    int nthreads;               // => Nº de threads
    
    int base_cod_prog;          // => Inicio do segmento com as instruções do programa
    int lim_cod_prog;           // => Dimensão do segmento com as instruções do programa
    
    int base_var_prog;          // => Inicio do segmento com as variáveis do programa
    int lim_var_prog;           // => Dimensão do segmento com as variáveis do programa
    
    int base_cod_thread;        // => Inicio do segmento com as instruções da thread
    int lim_cod_thread;         // => Dimensão do segmento com as instruções da thread
    
    int base_var_thread[4];     // => Inicio do segmento com as variáveis das threads
    int lim_var_thread[4];      // => Dimensão do segmento com as variáveis das threads
    int total_lim_var_thread;
    
    int activeThreads;
    
};

struct TCB{
    int pc;                     // => program counter do processo principal
    int pcs[4];                 // => program das threads
    int threadState;            // => estado da thread principal | New - 1 | Ready - 2 | Running - 3 | Block - 4 | Exit - 5
    int threads_state[4];       // => estado das threads         | New - 1 | Ready - 2 | Running - 3 | Block - 4 | Exit - 5
    int mainID;                 // => id do processo principal
    int threadsID[4];           // => ids das threads
    
    int thrdToWait;
    
    int burstTime;
    int thrdBurstTime[4];
    
    int isBlocked;                // => Se estiver à espera de threads
    int goToDisk;
    int thrdgoToDisk[4];
    int skipHalt;
    int showedOnce;
    
};


int nextFit(struct SO data, int sz);

int blocked2Ready(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread);
int run2exit_blocked_run(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst, int goToDisk);
int new2ready(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst);
int Ready2run(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread);
int Join2Ready(struct SO sist, struct PCB p, struct TCB t, int isBlocked, int nThread);
int removeProcess(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst);
int execute(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst);

#endif /* functions_h */
