//------------------------------------------------------------------------------------//
// Trabalho de S.O.(Simulador de Sistema Operativo com Modelo de 5 Estados com threads e
// Gestão de Memória por segmentação)

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566), João Condeço (nº 48976) e João Oliveira (nº 48979)
// Junho de 2022
//-----------------------------------------------------------------------------------//

#include "functions.h"
#include "queue.h"


//verifica a transição de estado de BLOCKED para READY
int blocked2Ready(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread){
    // => Se já tiver concluido:
    if(!isThread && t.burstTime >= 4){
        if(t.threadState != 4) return 0;
        //Verificar se está alguém em run
        if(Front(sist.blocked) == t.mainID){
            return 1;
        }
        else{
            return 0;
        }
    }
    // => Se já tiver concluido e for thread:
    else if(isThread && t.thrdBurstTime[nThread] == 4){
        if(t.threads_state[nThread] != 4) return 0;
        //Verificar se está alguém em run
        if(Front(sist.blocked) == t.threadsID[nThread]){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

//verifica a transição de estado de BLOCKED para READY
int Join2Ready(struct SO sist, struct PCB p, struct TCB t, int isBlocked, int nThread){
    // => Se já tiver concluido:
    if(t.isBlocked && t.threads_state[t.thrdToWait] == 6){
        return 1;
    }
    return 0;
}

int Ready2run(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread){
    return (t.threadState == 2 && !isThread && sist.whoIsRunning == -1 && Front(sist.ready) == t.mainID) ||
            (t.threads_state[nThread] == 2 && isThread && sist.whoIsRunning == -1 && Front(sist.ready) == t.threadsID[nThread]);
}

//transição run para outros
int run2exit_blocked_run(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst, int goToDisk){
    if(!isThread && goToDisk){
        if(t.threadState != 3 && inst != 6) return 0;
        return 4; // => (Block code)
    }
    else if(!isThread && (t.burstTime == sist.quantum)){
        if(t.threadState != 3) return 0;
        return 2; // => (Ready Code)
    }
    else if(!isThread && (inst == 20)){
        if(t.threadState != 3) return 0;
        return 5;
    }
    else if(isThread && goToDisk){
        if(t.threads_state[nThread] != 3 && inst != 6) return 0;
        return 4; // => (Block code)
    }
    else if(isThread && (t.thrdBurstTime[nThread] == sist.quantum)){
        if(t.threads_state[nThread] != 3) return 0;
        return 2; // => (Ready Code)
    }
    else if(isThread && (inst == 20)){
        if(t.threads_state[nThread] != 3) return 0;
        return 5;
    }
    
    return 0;
}

int new2ready(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst){
    if(!isThread && t.threadState == 1){
        return 1;
    }
    if(isThread && t.threads_state[nThread] == 1){
        return 1;
    }
    else{
        return 0;
    }
}


int removeProcess(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst){
    if((!isThread && t.threadState == 5) || (isThread && inst == 12)){
        return 1;
    }
    return 0;
}

int execute(struct SO sist, struct PCB p, struct TCB t, int isThread, int nThread, int inst){
    return (!isThread && t.threadState == 3) || (isThread && t.threads_state[nThread] == 3);
}

int nextFit(struct SO data, int sz){
    int found = 0;
    for (int i = data.pos; i < 200; i++){
        if(data.storage[i] == -1){
            found = 1;
            if(i+sz < 200){
            	for(int j = i; (j < i + sz) && (j < 200); j++){
                	if(data.storage[j] != -1){
                    	found = 0;
                    	break;
               	 	}
            	}
            	if(found){
                	return i;
            	}
            }
        }
    }
    return -1;
}
