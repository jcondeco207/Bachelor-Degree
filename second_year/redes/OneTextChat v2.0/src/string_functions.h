#ifndef string_functions_h
#define string_functions_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include "list.h"



#define PORT 1234
#define MAX_CLIENTS 30
#define FAMILY AF_INET
#define true 1
#define false 0
#define userLenght 20 
#define tagLenght 32

struct info{
      int num;
      char* username ;
      List tags;
};

int compareStrings(char *line1, char *line2);

int getDestiny(char bf[], char *str);

char *getTag(char bf[], int lenght);

int getName(char bf[], struct info sockets[]);

int getNameOLD(char bf[], struct info sockets[]);

char* getFileName(char bf[]);

int msgPos(char bf[], int lenght);

int requestValue(char bf[]);

int pow_jc(int b, int e);

int NumberToInt(char c[]);

int fileSZ(char bf[], int lenght);

#endif /* string_functions_h */