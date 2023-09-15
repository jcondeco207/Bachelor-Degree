#include <stdio.h>
#include <stdlib.h>
#include "client_functions.h"


int main(int argc, const char * argv[]) {
    if(argc < 3){
        printf("Argumentos insuficientes\n");
        return -1;
    }

    const char *name = argv[1];
    int port = atoi(argv[2]);

    runClient(name, port);
    return 0;
}
