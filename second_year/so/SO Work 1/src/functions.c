#include "functions.h"
#include "queue.h"




void printArray(int arr[][10]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 10; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

struct geral processHandler2(struct geral g, int instante, int robin){
    if(!robin){
        g.Quantum = g.comp;
    }
    
    for(int i = 0; i < g.nprocesses; i++){
        //Se estiver no running
        if(g.states[i] == 3){
            //Se acabou
            
            if(g.data[i].p[g.pos[i]] == 1){
                g.pos[i]++;
                g.running = -1;               
                if(g.pos[i] == (g.comp - 1) || g.data[i].p[g.pos[i]+1] == 0){
                    g.states[i] = 5;
                }
                else{
                    g.states[i] = 4;
                    Enqueue(i, g.blocked);
                }
            }
            else if((instante + 1) - g.data[i].beginRun >= g.Quantum){
                g.states[i] = 2;
                Enqueue(i, g.ready);
                g.running = -1;
                g.data[i].p[g.pos[i]]--;
                
            }
            else{
                g.data[i].p[g.pos[i]]--;
           }
        }
    }
    
    for(int i = 0; i < g.nprocesses; i++){
        //Quando ainda não é nada
        //printf("Primeira posição no array: %d\n", data.p[i][0]);


        if(g.data[i].p[0] == instante){ //segmentation fault i=2  
            g.states[i] = 1;
            g.data[i].p[0] = -1;
            g.pos[i] = 1;
        }
        
        //Se já for algo
        else if (g.data[i].p[0] == -1){
            // Se tiver no ready e tiver na frente da fila (e ninguém tiver no running)
            if(g.states[i] == 2  &&  g.ready->Array[Front(g.ready)] == i && g.running == -1){
                g.states[i] = 3;     //Passa a running
                g.data[i].beginRun = instante + 1;
                Dequeue(g.ready);    //Sai da queue do ready
                g.running = i;       //Passa a ser o processo do runnning
            }
            
            //Se tiver no blocked
            else if (g.states[i] == 4 ){
                //Se já teve o tempo suficiente
                if(g.data[i].p[g.pos[i]] == 0 && g.blocked->Array[g.blocked->Front] == i){
                    g.pos[i]++;
                    //Passar diretamente do Block pro Run
                    if(g.running == -1 && IsEmpty(g.ready)){
                        g.states[i] = 3;
                        g.data[i].beginRun = instante + 1;
                        g.running = i;
                    }
                    else{
                        g.states[i] = 2;    //Passa a ready
                        Enqueue(i, g.ready); // Vai para a queue do ready
                    }
                    
                    Dequeue(g.blocked);  // Sai da queue do blocked
                }
                else{
                    g.data[i].p[g.pos[i]]--;   //Caso contrário subtrai ao tempo que lá deve tar
                }
            }
            
                        
            //Se tiver no new
            else if(g.states[i] == 1){
                if(IsEmpty(g.ready) && g.running == -1){
                    g.running = i;
                    g.states[i] = 3;
                    g.data[i].beginRun = instante + 1;
                }
                else{
                    g.states[i] = 2;
                    Enqueue(i, g.ready);
                }
            }
            
            //Se tiver no Exit
            else if(g.states[i] == 5){
                g.states[i] = 6;
            }
            else if(g.states[i] == 6){
                g.states[i] = 0;
            }
        }
    }
    
    return g;
}
