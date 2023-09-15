//----------------------------------------------------------//
// 1º Trabalho de Redes de Computadores

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566) e João Condeço (nº 48976)
// Abril de 2022
//----------------------------------------------------------//

#ifndef server_functions_h
#define server_functions_h

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


#define PORT 1234
#define MAX_CLIENTS 30
#define FAMILY AF_INET
#define true 1
#define false 0
#define userLenght 20 



int runServer(void);

struct info{
      int num;
      char* username ;
};


#endif /* server_functions_h */
