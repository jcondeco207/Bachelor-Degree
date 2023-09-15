#include "list.h"
#include <stdlib.h>
#include "fatal.h"
#include <string.h>

/* Place in the interface file */
struct Node{
    ElementType Element;
    Position Next;
};

int compare(char *line1, char *line2){
    int test = 1;
    for (int i = 0; i < strlen(line1) - 1; i++) {
        if(line1[i] != line2[i]){
            test = 0;
        }
    }
    return test;
}

// => Esvazia a lista
List MakeEmpty(List L){
    if(L != NULL){
        DeleteList(L);
    }
     
    L = malloc(sizeof(struct Node));
    L->Next = NULL; 
    return L;
}

// => Verifica se a lista está vazia
int IsEmpty(List L){
    return L->Next == NULL;
}

// => Verifica se P é o último na Lista
int IsLast(Position P, List L){
    if(P->Next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

// => Devolve a posição do último elemento da Lista
Position getLast(List L){
     Position P = First(L);
     while(!IsLast(P, L)){
         P = P->Next;
     }
     return P;
}

// => Encontra a posição de X na lista
Position Find(ElementType X, List L){ 
     Position P2 = First(L);
    if(!strcmp(P2->Element, X)){
        return P2;
    }
    while(P2->Next != NULL){
        if(!strcmp(P2->Element, X)){
            return P2;
        }
        P2 = P2->Next;
    }
    if(!strcmp(P2->Element, X)){
        return P2;
    }
    return NULL;
}

// => Verifica se a tag X existe na lista
int existsTag(ElementType X, List L){
    if(Find(X,L) == NULL){
        return 0;
    }

    return 1;
}

// => Apaga elemento X da lista
void Delete( ElementType X, List L ){
    Position P = Find(X, L);
    int x = IsLast(P, L);
    if(First(L) == P){
        L->Next = P->Next;
    }
    else if (IsLast(P, L)){
        Position Prv = FindPrevious(X, L);
        Prv->Next = NULL;
    }
    else{
        Position Prv = FindPrevious(X, L);
        Prv->Next = P->Next;
    }

     free(P->Element);
     free(P);
}

// => Encontra a posição anterior a X
Position FindPrevious(ElementType X, List L){
     Position P2 = First(L);
     
     if(P2->Element == X){
        return NULL;
     }

     while(P2->Next != NULL){ 
        if(!strcmp(P2->Next->Element, X)){
            return P2;
        }
        P2 = P2->Next; 
     }
    return P2;
}

// => Insere um elemento na lista
void Insert(ElementType X, List L){
    Position P = malloc(sizeof(struct Node));
    P->Element = (char *)calloc(strlen(X), sizeof(char)*strlen(X));
    strcpy(P->Element, X);
    if(IsEmpty(L)){
        L->Next = P;
        P->Next = NULL;
        return;
    }
    
    Position P2 = First(L);
    while(P2->Next != NULL){
        P2 = P2->Next;
    }

    P2->Next = P;
    P->Next = NULL;
}

// => Apaga a Lista
void DeleteList(List L) {
     while(!IsEmpty(L)){
        Position P = getLast(L);
        Delete(P->Element, L);
     }
     free(L);
}

Position Header(List L){
    return L;
}

Position First(List L){
    return L->Next;
}

Position Advance(Position P){
    return P->Next;
}

ElementType Retrieve(Position P){
    return P->Element;
}
 