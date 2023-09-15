//----------------------------------------------------------//
// 1º Trabalho de Redes de Computadores

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566) e João Condeço (nº 48976)
// Abril de 2022
//----------------------------------------------------------//


#ifndef client_functions_h
#define client_functions_h

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include "list.h"

#define FAMILY AF_INET
#define true 1
#define false 0
#define postLenght 1024

void runClient(const char *name, int port);


#endif /* client_functions_h */
