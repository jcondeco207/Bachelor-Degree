//------------------------------------------------------------------------------------//
// Trabalho de S.O.(Simulador de Sistema Operativo com Modelo de 5 Estados com threads e
// Gestão de Memória por segmentação)

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566), João Condeço (nº 48976) e João Oliveira (nº 48979)
// Junho de 2022
//-----------------------------------------------------------------------------------//


#include <stdbool.h>

typedef int ElementType;

#ifndef _Queue_h
#define _Queue_h

struct QueueRecord{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

typedef struct QueueRecord *Queue;

int IsEmpty( Queue Q );
int IsFull( Queue Q );
Queue CreateQueue( int MaxElements );
void DisposeQueue( Queue Q );
void MakeEmpty( Queue Q );
void Enqueue( ElementType X, Queue Q );
ElementType Front( Queue Q );
void Dequeue( Queue Q );
ElementType FrontAndDequeue( Queue Q );
int returnAt(int i, Queue Q);
#endif  /* _Queue_h */
/* END */
