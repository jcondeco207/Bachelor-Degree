//
//  functions.h
//
//
//  Created by João Condeço and Sara Amaral on 30/05/2021.
//

#ifndef functions_h
#define functions_h

#define MAX_LENGHT 100

#include <stdio.h>

#include "hashsep.h"

#define tablesz 40000

struct updates {
    char new[100][10];
    char name[100];
    int posnew;
};

long int ToNumber(char l);

char toLower(char l);

int SizeCounter(char *str);

int NewHash(char *str, int tablesize);

void PrintChars(int n, char c);

char GetNumber(char l);

int Value(char *numbers);

void PrintTable(HashTable H);

int hashcode(char *numbers);

char *RetConvert(char *word);

char *normalize(char *str);

void upload(int hf);

int Receiver(HashTable H);

HashTable AddDict(HashTable H, const char *argv[], int argc, int ins, int *hf, int *loaded);

#endif /* functions_h */
