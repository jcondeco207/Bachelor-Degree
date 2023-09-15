//------------------------------------------------------------------------------------//
// Trabalho de S.O.(Simulador de Sistema Operativo com Modelo de 5 Estados com threads e
// Gestão de Memória por segmentação)

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566), João Condeço (nº 48976) e João Oliveira (nº 48979)
// Junho de 2022
//-----------------------------------------------------------------------------------//

#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"
#include <stdbool.h>
#include "functions.h"

#define MinQueueSize (0)


int IsEmpty(Queue Q){
    return Q->Size == 0;
}

int IsFull(Queue Q){
    return Q->Size == Q->Capacity;
}

Queue CreateQueue(int MaxElements){
    Queue Q;
    
    if(MaxElements < MinQueueSize)
        Error("O tamanho definido é demasiado reduzido");
    
    Q = malloc(sizeof(struct QueueRecord));
    
    if(Q == NULL)
        FatalError("Sem espaço disponível");
    Q->Array = malloc(sizeof(ElementType) * MaxElements);
    
    if(Q->Array == NULL)
        FatalError("Sem espaço disponível");
    Q->Capacity = MaxElements;
    MakeEmpty( Q );
    return Q;
}

void MakeEmpty(Queue Q){
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}


void DisposeQueue(Queue Q){
    if(Q != NULL){
        free(Q->Array);
        free(Q);
        
    }
}

static int Succ(int Value, Queue Q){
    if(++Value == Q->Capacity)
        Value = 0;
    return Value;
}

void Enqueue(ElementType X, Queue Q){
    if(!IsFull(Q)){
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

ElementType Front(Queue Q){
    if(!IsEmpty(Q))
        return Q->Array[Q->Front];
    return 0;
}

void Dequeue(Queue Q){
    if(!IsEmpty(Q)){
        Q->Size--;
        Q->Front = Succ(Q->Front, Q);
    }
}

int returnAt(int i, Queue Q){
    return Q->Array[i];
}

