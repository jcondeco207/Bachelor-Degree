//------------------------------------------------------------------------------------//
// Trabalho de S.O.(Simulador de Sistema Operativo com Modelo de 5 Estados com threads e
// Gestão de Memória por segmentação)

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566), João Condeço (nº 48976) e João Oliveira (nº 48979)
// Junho de 2022
//-----------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


//Função que imprime o cabeçalho 
void printTitle(){
    printf("\033[0;33m\n           \n           ____                                _   _                 _ _\n          |  _ \\ _ __ ___   ___ ___  ___ ___  | | | | __ _ _ __   __| | | ___ _ __\n          | |_) | '__/ _ \\ / __/ _ \\/ __/ __| | |_| |/ _` | '_ \\ / _` | |/ _ \\ '__|\n          |  __/| | | (_) | (_|  __/|__ |__ \\ |  _  | (_| | | | | (_| | |  __/ |\n          |_|   |_|  \\___/ \\___\\___||___/___/ |_| |_|\\__,_|_| |_|\\__,_|_|\\___|_|\033[0m\n\n");
    
    printf("\n\n");
}

void printOutput(struct TCB *t, struct PCB *p, int nprocesses, int instante){
    int count = 0;
    if(instante < 10){
        printf("0%d ", instante);
    }
    else{
        printf("%d ", instante);
    }
    
    for(int i = 0; i < nprocesses; i++){
        printf(" ");
    }
    printf("| ");
    //New
    for (int i = 0; i < nprocesses; i++) {
        if(t[i].threadState == 1){
            printf("P%d ", (i+1));
            count+=3;
        }
        for(int j = 0; j < p[i].nthreads; j++){
            if(t[i].threads_state[j] == 1){
                printf("TH%d ", (j+1));
                count+=4;
            }
        }
    }
    for(int i = 0; i < 11 - count; i++){
        printf(" ");
    }
    count = 0;
    printf("| ");
    
    //Ready
    for (int i = 0; i < nprocesses; i++) {
        if(t[i].threadState == 2){
            printf("P%d ", (i+1));
            count+=3;
        }
        for(int j = 0; j < p[i].nthreads; j++){
            if(t[i].threads_state[j] == 2){
                printf("TH%d ", (j+1));
                count+=4;
            }
        }
    }
    for(int i = 0; i < 13 - count; i++){
        printf(" ");
    }
    count = 0;
    printf("| ");
    
    //Run
    for (int i = 0; i < nprocesses; i++) {
        if(t[i].threadState == 3){
            printf("P%d ", (i+1));
            count+=3;
        }
        for(int j = 0; j < p[i].nthreads; j++){
            if(t[i].threads_state[j] == 3){
                printf("TH%d ", (j+1));
                count+=4;
            }
        }
    }
    for(int i = 0; i < 11 - count; i++){
        printf(" ");
    }
    count = 0;
    printf("| ");
    
    //Blocked
    for (int i = 0; i < nprocesses; i++) {
        if(t[i].threadState == 4){
            printf("P%d ", (i+1));
            count+=3;
        }
        for(int j = 0; j < p[i].nthreads; j++){
            if(t[i].threads_state[j] == 4){
                printf("TH%d ", (j+1));
                count+=4;
            }
        }
    }
    for(int i = 0; i < 15 - count; i++){
        printf(" ");
    }
    count = 0;
    printf("| ");
    
    //Exit
    for (int i = 0; i < nprocesses; i++) {
        if(t[i].threadState == 5 || t[i].threadState == 6){
            printf("P%d ", (i+1));
            count+=3;
        }
        for(int j = 0; j < p[i].nthreads; j++){
            if(t[i].threads_state[j] == 5){
                printf("TH%d ", (j+1));
                count+=4;
            }
        }
    }
    for(int i = 0; i < 12 - count; i++){
        printf(" ");
    }
    count = 0;
    printf("| ");
    
    printf("\n");
}

//Função responsável por comparar duas Strings (retorna 1 se forem iguais | retorna 0 se forem diferentes)
int compareStrings(char *line1, char *line2){
    int test = 1;
    
    for (int i = 0; i < 4; i++) {
        //printf("%c == %c  pos: %d\n", line1[i], line2[i], i);
        if(line1[i] != line2[i]){
            test = 0;
        }
    }
    //printf("\n");
    return test;
}

int getCode(char inst[]){
    if(compareStrings(inst, "ZERO")){
        return 0;
    }
    else if(compareStrings(inst, "COPY")){
        return 1;
    } 
    else if(compareStrings(inst, "DECR")){
        return 2;
    }
    else if(compareStrings(inst, "NWTH")){
        return 3;
    }
    else if(compareStrings(inst, "JFRW")){
        return 4;
    }
    else if(compareStrings(inst, "JBCK")){
        return 5;
    }
    else if(compareStrings(inst, "DISK")){
        return 6;
    }
    else if(compareStrings(inst, "JIFZ")){
        return 7;
    }
    else if(compareStrings(inst, "PRNT")){
        return 8;
    }
    else if(compareStrings(inst, "JOIN")){
        return 9;
    }
    else if(compareStrings(inst, "ADDX")){
        return 10;
    }
    else if(compareStrings(inst, "MULX")){
        return 11;
    }
    else if(compareStrings(inst, "RETN")){
        return 12;
    }
    else if(compareStrings(inst, "LOAD")){
        return 13;
    }
    else if(compareStrings(inst, "ENDP")){
        return 14;
    }
    else if(compareStrings(inst, "THRD")){
        return 15;
    }
    else if(compareStrings(inst, "HALT")){
        return 20;
    }
    else{
        printf("Instrução inválida\n");
        exit(1);
    }
}

int countProcess(){
    int nprocesses = 0;

    FILE *myf;

    myf = fopen("input1.txt", "r");

    if (myf == NULL) {
        printf("\nFicheiro indisponível.\n\n");
        exit(1);
    }
    else{
        char inst[4];
        bzero(inst, 4);
        memset(inst, 0, 4);

        int n;

        while(1){
            if(fscanf(myf, "%c%c%c%c %d\n", &inst[0], &inst[1], &inst[2], &inst[3], &n)==EOF) break;
            //printf("%c%c%c%c %d the code: %d nprocesses: %d\n" , inst[0], inst[1], inst[2], inst[3], n, getCode(inst), nprocesses);
            if(getCode(inst) == 13){
                nprocesses++;
            }

            bzero(inst, 4);
            memset(inst, 0, 4);
        }
   }
   return nprocesses;
}

int main(int argc, const char * argv[]) {
    printTitle();
    printf(" T  |     NEW    |     READY    |     RUN    |     BLOCKED    |     EXIT    |\n");
    FILE *myf;
    int nprocesses = countProcess();
    struct PCB p[nprocesses];
    struct TCB t[nprocesses];
    
    
    for(int i = 0; i < nprocesses; i++){
        p[i].loadTime = -1;
        p[i].nthreads = 0;
        p[i].ninsts = 0;
        p[i].ninsts_thread = 0;
        p[i].maxVar = -1;
        p[i].base_cod_prog = -1;
        p[i].lim_cod_prog = 0;
        p[i].base_var_prog = -1;
        p[i].lim_var_prog = 0;
        p[i].base_cod_thread = -1;
        p[i].lim_cod_thread = 0;
        p[i].total_lim_var_thread = 0;
        p[i].activeThreads = 0;
        //Inicializar arrays das threads
        for(int j = 0; j < 4; j++){
            p[i].base_var_thread[j] = -1;
            p[i].lim_var_thread[j] = 0;
        }
        
        t[i].pc = 0;
        t[i].mainID = -1;
        t[i].threadState = -1;
        t[i].burstTime = 0;
        t[i].isBlocked = 0;
        t[i].thrdToWait = -1;
        t[i].goToDisk = 0;
        t[i].skipHalt = 0;
        t[i].showedOnce = 0;
        
        for(int j = 0; j < 4; j++){
            t[i].pcs[j] = 0;
            t[i].threadsID[j] = -1;
            t[i].threads_state[j] = -1;
            t[i].thrdBurstTime[j] = 0;
            t[i].thrdgoToDisk[j] = 0;
        }
    }
    
    //Inicializar as Queues
    for(int i = 0; i < nprocesses; i++){
        Queue code = CreateQueue(100);
        p[i].code = code;
        Queue var = CreateQueue(100);
        p[i].var = var;
        MakeEmpty(p[i].code);
        MakeEmpty(p[i].var);
        p[i].maxVar = -1;
    }
    
    
    
    int instante = 0;
    int start = -1;
    int maxThread;

    myf = fopen("input1.txt", "r");

    if (myf == NULL) {
        printf("\nFicheiro indisponível.\n\n");
        exit(1);
    }
    else{
        char inst[4];
        bzero(inst, 4);
        memset(inst, 0, 4);

        int n;
        int ninsts = 0;
        maxThread = 0;
        int finding_in_thread = 0;
        while(1){
            if(fscanf(myf, "%c%c%c%c %d\n", &inst[0], &inst[1], &inst[2], &inst[3], &n)==EOF) break;
            //LOAD
            if(getCode(inst) == 13){
                start++;
                p[start].loadTime = n;
            }
            //THRD
            else if(getCode(inst) == 15){
                p[start].ninsts = ninsts;
                ninsts = 0;
                finding_in_thread = 1;
                maxThread = 0;
            }
            //RETN
            else if (getCode(inst) == 12){
                p[start].maxVarThread = maxThread;
                Enqueue(getCode(inst), p[start].code);
                Enqueue(n, p[start].var);
                ninsts++;
            }
            //ENDP
            else if(getCode(inst) == 14){
                p[start].ninsts_thread = ninsts;
                ninsts = 0;
                finding_in_thread = 0;
            }
            //New Thread
            else if(getCode(inst) == 3){
                Enqueue(getCode(inst), p[start].code);
                Enqueue(n, p[start].var);
                ninsts++;
                p[start].nthreads++;
            }
            else if(start >= 0){
                Enqueue(getCode(inst), p[start].code);
                Enqueue(n, p[start].var);
                ninsts++;
                if((p[start].maxVar < n) && (getCode(inst) != 0) && (!finding_in_thread))
                    p[start].maxVar = n;
                else if((maxThread < n) && (getCode(inst) != 0) && (finding_in_thread) && (n <= 9))
                    maxThread = n;
            }

            bzero(inst, 4);
            memset(inst, 0, 4);
        }
    }
    
    //Setup da memória
    struct SO sist;
    sist.pos = 0;
    sist.whoIsRunning = -1;
    sist.lastID = -1;
    sist.quantum = 3;
    sist.instsAlocated = 0;
    memset(sist.mem, -1, sizeof(sist.storage));
    memset(sist.storage, -1, sizeof(sist.storage));
    int queuesDim = nprocesses;
    if( nprocesses == 1 && p[0].nthreads == 0){
        sist.quantum = p[0].ninsts;
    }
    
    //Inicializar valores dos processos
    for(int i = 0; i < nprocesses; i++){
        p[i].lim_cod_prog = p[i].ninsts;
        p[i].lim_var_prog = p[i].maxVar + 1;
        p[i].lim_cod_thread = p[i].ninsts_thread;
        
        queuesDim += p[i].nthreads;
        for(int j = 0; j < p[i].nthreads; j++){
            p[i].lim_var_thread[j] = maxThread + 1;
            p[i].total_lim_var_thread += maxThread + 1;
        }
    }
    
    sist.blocked = CreateQueue(queuesDim);
    sist.ready = CreateQueue(queuesDim);
    sist.joinBlocked = MakeEmptyList(NULL);
    MakeEmpty(sist.blocked);
    MakeEmpty(sist.ready);
    
    int cont = 1;
    //Decorrer do programa
    while(instante < 100 && cont){
        
        int toRun = sist.whoIsRunning;
        int wait = 0;
        int pToWait = -1;
        int getRetn = 0;
        int getJoin = 0;
        
        for(int i = 0; i < nprocesses; i++){
            // => Se o processo não tiver bloqueado por threads
            if(!t[i].isBlocked){
                // => Verifica se pode passar de blocked para ready
                if(blocked2Ready(sist, p[i], t[i], t[i].isBlocked, 0)){
                    t[i].threadState = 2;
                    Enqueue(t[i].mainID, sist.ready);
                    Dequeue(sist.blocked);
                    t[i].burstTime = 0;
                }
            }
            else if(Join2Ready(sist, p[i], t[i], t[i].isBlocked, 0)){
                if(IsEmpty(sist.ready)) wait = 1;
                pToWait = t[i].mainID;
                t[i].thrdToWait = -1;
                t[i].isBlocked = 0;
                Delete(t[i].mainID, sist.joinBlocked);
                Enqueue(t[i].mainID, sist.ready);
                t[i].threadState = 2;
                t[i].burstTime = 0;
            }
            
            // => Se estiver a lidar com threads do processo
            // => Vai verificar todas as threads
            for(int j = 0; j < p[i].nthreads; j++){
                // => E passa para ready aquelas que puder
                if(blocked2Ready(sist, p[i], t[i], t[i].isBlocked, j)){
                    t[i].threads_state[j] = 2;
                    Enqueue(t[i].threadsID[j], sist.ready);
                    Dequeue(sist.blocked);
                    t[i].thrdBurstTime[j] = 0;
                }
            }
        }
        
        for(int i = 0; i < nprocesses; i++){
            if(run2exit_blocked_run(sist, p[i], t[i], t[i].isBlocked, 0, sist.mem[t[i].pc], t[i].goToDisk)){
                int nextState = run2exit_blocked_run(sist, p[i], t[i], t[i].isBlocked, 0, sist.mem[t[i].pc], t[i].goToDisk);
                t[i].threadState = nextState;
                sist.whoIsRunning = -1;

                if(nextState == 2){
                    t[i].burstTime = 0;
                    Enqueue(t[i].mainID, sist.ready);
                }
                else if(nextState == 4){
                    wait = 1;
                    pToWait = t[i].mainID;
                    t[i].burstTime = 0;
                    Enqueue(t[i].mainID, sist.blocked);
                    t[i].goToDisk = 0;
                }
                else if(nextState == 5){
                    t[i].burstTime = 0;
                }    
            }

            for(int j = 0; j < p[i].nthreads; j++){
                if(run2exit_blocked_run(sist, p[i], t[i], 1, j, sist.mem[t[i].pc], t[i].thrdgoToDisk[j])){
                    int nextStateThrd = run2exit_blocked_run(sist, p[i], t[i], 1, j, sist.mem[t[i].pc], t[i].thrdgoToDisk[j]);
                    t[i].threads_state[j] = nextStateThrd;
                    sist.whoIsRunning = -1;

                    if(nextStateThrd == 2){
                        t[i].thrdBurstTime[j] = 0;
                        Enqueue(t[i].threadsID[j], sist.ready);
                    }
                    else if(nextStateThrd == 4){
                        t[i].thrdBurstTime[j] = 0;
                        Enqueue(t[i].threadsID[j], sist.blocked);
                        t[i].thrdgoToDisk[j] = 0;
                    }
                    else if(nextStateThrd == 5){
                        t[i].thrdBurstTime[j] = 0;
                    }
                }
            }
        }
        
        //New to Ready
        for(int i = 0; i < nprocesses; i++){
            if(!t[i].isBlocked){
                if(new2ready(sist, p[i], t[i], t[i].isBlocked, 0, sist.mem[t[i].pc])){
                    t[i].threadState = 2;
                    Enqueue(t[i].mainID, sist.ready);
                }
            }
            
            // => Vai verificar todas as threads
            for(int j = 0; j < p[i].nthreads; j++){
                // => E passa para ready aquelas que puder
                if(new2ready(sist, p[i], t[i], 1, j, sist.mem[t[i].pc])){
                    t[i].threads_state[j] = 2;
                    Enqueue(t[i].threadsID[j], sist.ready);
                }
            }
        }
        
        // Ready -> Run
        for(int i = 0; i < nprocesses; i++){
            if(!t[i].isBlocked){
                if(Ready2run(sist, p[i], t[i], t[i].isBlocked, 0)){
                    t[i].threadState = 3;
                    //Na inserção inicial
                    if(sist.whoIsRunning == -1)
                        toRun = t[i].mainID;
                    sist.whoIsRunning = t[i].mainID;
                    Dequeue(sist.ready);
                }
            }
            for(int j = 0; j < p[i].nthreads; j++){
                if(Ready2run(sist, p[i], t[i], 1, j)){
                    t[i].threads_state[j] = 3;
                    //Na inserção inicial
                    if(sist.whoIsRunning == -1)
                        toRun = t[i].threadsID[j];

                    sist.whoIsRunning = t[i].threadsID[j];
                    Dequeue(sist.ready);
                }
            }
        }
        
        //NewProcess
        for(int i = 0; i < nprocesses; i++){
            //Recebe novos processos
            if(p[i].loadTime == instante){
                //Inicializa o processo NewProcess
                t[i].mainID = sist.lastID + 1;
                sist.lastID++;
                int dim = p[i].lim_var_prog + p[i].lim_cod_prog;
                int posP = nextFit(sist, dim);
                if(posP == -1){
                    printf("> Impossivel criar o processo número %d, o espaço disponivel em memória é insuficiente.\n", i);
                    continue;
                }
                for(int j = posP; j < (dim + posP); j++){
                    sist.storage[j] = t[i].mainID;
                }
                p[i].base_cod_prog = posP;
                p[i].base_var_prog = posP + p[i].lim_cod_prog;
                p[i].base_cod_thread = p[i].lim_var_prog + p[i].base_var_prog;
                t[i].threadState = 1;
                t[i].pc = posP;
                
                for(int j = 0; j < p[i].nthreads; j++){
                    p[i].base_var_thread[j] = p[i].base_cod_thread + p[i].lim_cod_thread + (p[i].maxVarThread * j);    
                }
                
                for(int j = p[i].base_cod_prog; j < (p[i].lim_cod_prog + p[i].base_cod_prog); j++){
                    sist.mem[j] = Front(p[i].code);
                    sist.params[j] = Front(p[i].var);
                    Dequeue(p[i].code);
                    Dequeue(p[i].var);
                }
            }
        }
        
        //Remove Process - EXIT
        for(int i = 0; i < nprocesses; i++){
            if(!t[i].isBlocked){
                if(removeProcess(sist, p[i], t[i], t[i].isBlocked, 0, sist.mem[t[i].pc])){
                    t[i].threadState = 6;
                    for(int j = 0; j < 200; j++){
                        if(sist.storage[j] == t[i].mainID){
                            sist.mem[j] = -1;
                            sist.storage[j] = -1;
                        }
                    }
                }
            }
        }
        
        //Execute - Run
        for(int i = 0; i < nprocesses; i++){
            if(wait && pToWait == t[i].mainID) break;
            
            if(!t[i].isBlocked && t[i].mainID == toRun){
                if(execute(sist, p[i], t[i], t[i].isBlocked, 0, sist.mem[t[i].pc])){
                    int inst = sist.mem[t[i].pc];
                    int var = sist.params[t[i].pc];
                    
                    if(inst == 0){ //ZERO
                        sist.mem[p[i].base_var_prog] = var;
                        t[i].pc++;
                        t[i].burstTime++;
                    }
                    else if(inst == 1){//COPY
                        sist.mem[var + p[i].base_var_prog] = sist.mem[p[i].base_var_prog];
                        t[i].pc++;
                        t[i].burstTime++;
                    }
                    else if(inst == 2){//DECR
                        sist.mem[var + p[i].base_var_prog]--;
                        t[i].pc++;  
                        t[i].burstTime++;                         
                    }
                    else if(inst == 3){//NWTH
                        int dim = p[i].lim_cod_thread;
                        int posP = nextFit(sist, dim);
                        p[i].activeThreads++;
                        if(posP == -1){
                            printf("> Impossivel criar thread número %d do processo %d, o espaço disponivel em memória é insuficiente.\n", var, (i+1));
                        }
                        
                        var--;
                        sist.lastID++;
                        
                        t[i].threadsID[var] = sist.lastID;
                        
                        if(!sist.instsAlocated){
                            p[i].base_cod_thread = posP;
                        
                            for(int j = posP; j < (p[i].base_cod_thread + p[i].lim_cod_thread); j++){
                                sist.storage[j] = t[i].threadsID[var];
                                sist.mem[j] = Front(p[i].code);
                                sist.params[j] = Front(p[i].var);
                                Dequeue(p[i].code);
                                Dequeue(p[i].var);
                            }
                            sist.instsAlocated = 1;
                        }
                        
                        dim = p[i].lim_var_thread[var];
                        posP = nextFit(sist, dim);
                        t[i].pcs[var] = p[i].base_cod_thread;
                        
                        p[i].base_var_thread[var] = posP;
                        t[i].threads_state[var] = 2;
                        
                        for(int j = posP; j < (p[i].base_var_thread[var] + dim); j++){
                            sist.storage[j] = t[i].threadsID[var];
                        }
                        sist.mem[p[i].base_var_thread[var]] = sist.mem[p[i].base_var_prog + (var + 1)]; // var 0 da thread = var x do processo
                        sist.mem[p[i].base_var_thread[var] + 1] = (var + 1); // var 1 da thread = n thread
                        t[i].pc++;
                        t[i].burstTime++;
                        Enqueue(t[i].threadsID[var], sist.ready);
                    
                    }
                    
                    else if(inst == 4){//JFWR
                        var++;
                        if(t[i].pc + var > (p[i].ninsts + p[i].base_cod_prog)){
                            t[i].threadState = 5;
                            printf("O processo avançou para fora do bloco de instruções\n");
                        }
                        else{
                            t[i].pc += var;
                            t[i].burstTime++;
                        }
                    }
                    else if(inst == 5){//JBCK
                        if(t[i].pc - var < 0){
                            t[i].threadState = 5;
                            printf("O processo recuou para fora do bloco de instruções\n");
                        }
                        else{
                            t[i].pc -= var;
                            t[i].burstTime++;
                        }
                    }
                    else if(inst == 6){//DISK
                        t[i].goToDisk = 1;
                        t[i].pc++;
                        t[i].burstTime++;
                    }
                    else if(inst == 7){//JIFZ
                        if(sist.mem[p[i].base_var_prog + var] == 0 && t[i].pc + 2 > (p[i].ninsts + p[i].base_cod_thread)){
                            t[i].threadState = 5;
                            printf("O processo saltou para fora do bloco de instruções\n");
                        }
                        else if(sist.mem[p[i].base_var_prog + var] == 0){
                            t[i].pc += 3;
                            t[i].burstTime++;
                        }
                        else{
                            t[i].pc++;
                        }
                    }
                    else if(inst == 8){//PRNT
                        //printf("PRNT %d no p%d\n", var, (i+ 1));
                        printf("> print %d\n", (sist.mem[p[i].base_var_prog + var]));
                        t[i].pc++;
                        t[i].burstTime++;
                    }
                    else if(inst == 9){//JOIN
                        if(t[i].threads_state[var - 1] != 6){
                            t[i].isBlocked = 1;
                            Insert(t[i].mainID, sist.joinBlocked);
                            sist.whoIsRunning = -1;
                            t[i].thrdToWait = (var - 1);
                            t[i].threadState = 4;
                        }
                        t[i].pc++;
                        getJoin = 1;
                    }
                    else if(inst == 10){//ADDX
                        sist.mem[p[i].base_var_prog] += sist.mem[p[i].base_var_prog + var];
                        t[i].pc++;
                        t[i].burstTime++;
                    }
                    else if(inst == 11){//MULX
                        sist.mem[p[i].base_var_prog] *= sist.mem[p[i].base_var_prog + var];
                        t[i].pc++;
                        t[i].burstTime++;
                    }
                    else if(inst == 20){//HALT
                        
                        t[i].threadState = 5;
                        sist.whoIsRunning = -1;
                        for (int j = 0; j < p[i].nthreads; j++) {
                            if(sist.whoIsRunning == t[i].threadsID[j]){
                                sist.whoIsRunning = -1;
                            }
                            for(int k = 0; k < 200; k++){
                                if(sist.storage[k] == t[i].threadsID[j]){
                                    sist.mem[k] = -1;
                                    sist.storage[k] = -1;
                                }
                            }
                        }
                        t[i].pc++;
                    }
                }
            }
            
            // => Vai verificar todas as threads
            for(int j = 0; j < p[i].nthreads; j++){
                // => E passa para ready aquelas que puder
                
                if(wait && pToWait == t[i].threadsID[j]) break;
                if(t[i].threadsID[j] != toRun) continue;
                
                if(execute(sist, p[i], t[i], 1, j, sist.mem[t[i].pc])){
                    int inst = sist.mem[t[i].pcs[j]];
                    int var = sist.params[t[i].pcs[j]];
                        
                    if(inst == 0){ //ZERO
                        sist.mem[p[i].base_var_thread[j]] = var;
                        t[i].pcs[j]++;
                        t[i].thrdBurstTime[j]++;
                    }
                    else if(inst == 1){//COPY
                        if(var > 9){
                            var = p[i].base_var_prog + var;
                            sist.mem[var] = sist.mem[p[i].base_var_thread[j]];
                        }
                        else{
                            sist.mem[p[i].base_var_thread[j] + var] = sist.mem[p[i].base_var_thread[j]];
                        }
                        t[i].pcs[j]++;
                        t[i].thrdBurstTime[j]++;
                    }
                    else if(inst == 2){//DECR
                        if(var > 9){
                            var = p[i].base_var_prog + var;
                            sist.mem[var + p[i].base_var_prog]--;
                        }
                        else{
                            sist.mem[var + p[i].base_var_thread[j]]--;
                        }
                        t[i].pcs[j]++;
                        t[i].thrdBurstTime[j]++;
                    }
                    else if(inst == 4){//JFWR
                        var++;
                        if(t[i].pcs[j] + var > (p[i].ninsts_thread + p[i].base_cod_thread)){
                            if(sist.whoIsRunning == t[i].threadsID[j]){
                                sist.whoIsRunning = -1;
                            }
                            for(int k = 0; k < 200; k++){
                                if(sist.storage[k] == t[i].threadsID[j]){
                                    sist.mem[k] = -1;
                                    sist.storage[k] = -1;
                                }
                            }
                            printf("> O processo avançou para fora do bloco de instruções\n");
                        }
                        else{
                            t[i].pcs[j] += var;
                            t[i].thrdBurstTime[j]++;
                        }
                    }
                    else if(inst == 5){//JBCK
                        if(t[i].pc - var < 0){
                            if(sist.whoIsRunning == t[i].threadsID[j]){
                                sist.whoIsRunning = -1;
                            }
                                    
                            for(int k = 0; k < 200; k++){
                                if(sist.storage[k] == t[i].threadsID[j]){
                                    sist.mem[k] = -1;
                                    sist.storage[k] = -1;
                                }
                            }
                            printf("> O processo recuou para fora do bloco de instruções\n");
                        }
                        else{
                            t[i].pcs[j] -= var;
                            t[i].thrdBurstTime[j]++;
                        }
                    }
                    else if(inst == 7){//JIFZ
                        if(sist.mem[p[i].base_var_thread[j] + var] == 0 && t[i].pcs[j] + 2 > (p[i].ninsts_thread + p[i].base_cod_thread)){
                            if(sist.whoIsRunning == t[i].threadsID[j]){
                                sist.whoIsRunning = -1;
                            }
                            
                            for(int k = 0; k < 200; k++){
                                if(sist.storage[k] == t[i].threadsID[j]){
                                    sist.mem[k] = -1;
                                    sist.storage[k] = -1;
                                }
                            }
                            printf("O processo saltou para fora do bloco de instruções\n");
                        }
                        else if(sist.mem[p[i].base_var_thread[j] + var] == 0){
                            t[i].pcs[j] += 3;
                            t[i].thrdBurstTime[j]++;
                        }
                        else{
                            t[i].pcs[j]++;
                            t[i].thrdBurstTime[j]++;
                        }
                    }
                    else if(inst == 8){//PRNT
                        printf("> print %d\n", (sist.mem[p[i].base_var_thread[j] + var]));
                        t[i].pc++;
                        t[i].thrdBurstTime[j]++;
                    }
                    else if(inst == 10){//ADDX
                        if(var > 9){
                            sist.mem[p[i].base_var_thread[j]] += sist.mem[p[i].base_var_prog + var];
                        }
                        else{
                            sist.mem[p[i].base_var_thread[j]] += sist.mem[p[i].base_var_thread[j] + var];
                        }
                        
                        t[i].pcs[j]++;
                        t[i].thrdBurstTime[j]++;
                    }
                    else if(inst == 11){//MULX
                        
                        if(var > 9){
                            sist.mem[p[i].base_var_thread[j]] *= sist.mem[p[i].base_var_prog + var];
                        }
                        else{
                            sist.mem[p[i].base_var_thread[j]] *= sist.mem[p[i].base_var_thread[j] + var];
                        }
                        
                        t[i].pcs[j]++;
                        t[i].thrdBurstTime[j]++;
                    }
                    else if(inst == 12){//RETN
                        getRetn = 1;
                        p[i].activeThreads--;
                        
                        if(sist.whoIsRunning == t[i].threadsID[j]){
                            sist.whoIsRunning = -1;
                        }
                        for(int k = 0; k < 200; k++){
                            if(sist.storage[k] == t[i].threadsID[j]){
                                if(p[i].activeThreads > 0 && ((k >= p[i].base_var_thread[j]) && (k < p[i].base_var_thread[j] + p[i].lim_var_thread[j]))){
                                    sist.mem[k] = -1;
                                    sist.storage[k] = -1;
                                }
                                else if (p[i].activeThreads == 0){
                                    sist.mem[k] = -1;
                                    sist.storage[k] = -1;
                                }
                            }
                        }
                        t[i].pcs[j]++;
                        t[i].thrdBurstTime[j]++;
                        t[i].threads_state[j] = 6;
                    }
                }
            }
        }
        
        // => Incrementa o burstTime das filas do blocked
        for(int i = 0; i < nprocesses; i++){
            if(t[i].threadState == 4 && t[i].mainID == Front(sist.blocked)){
                t[i].burstTime++;
            }
            for(int j = 0; j < nprocesses; j++){
                if(t[i].threads_state[j] == 4 && t[i].threadsID[j] == Front(sist.blocked)){
                    t[i].thrdBurstTime[j]++;
                }
            }
        }
        
        
        if(getRetn || getJoin){
            // Ready -> Run
            for(int i = 0; i < nprocesses; i++){
                if(!t[i].isBlocked){
                    if(Ready2run(sist, p[i], t[i], t[i].isBlocked, 0)){
                        t[i].threadState = 3;
                        //Na inserção inicial
                        if(sist.whoIsRunning == -1)
                            toRun = t[i].mainID;
                        sist.whoIsRunning = t[i].mainID;
                        Dequeue(sist.ready);
                    }
                }
                for(int j = 0; j < p[i].nthreads; j++){
                    if(Ready2run(sist, p[i], t[i], 1, j)){
                        t[i].threads_state[j] = 3;
                        //Na inserção inicial
                        if(sist.whoIsRunning == -1)
                            toRun = t[i].threadsID[j];
                        sist.whoIsRunning = t[i].threadsID[j];
                        Dequeue(sist.ready);
                    }
                }
            }
            getRetn = 0;
        }
        
        // => Verifica quando o programa termina
        printOutput(t, p, nprocesses, instante);
        cont = 0;
        for(int i = 0; i < nprocesses; i++){
            if(t[i].threadState < 5)
                cont = 1;
            if(t[i].threadState == 6){
                t[i].threadState = 7;
            }
            
        }
        
        instante++;
    }
    
    printf("\n\n");
    return 0;
}
