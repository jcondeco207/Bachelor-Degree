//----------------------------------------------------------//
// 1º Trabalho de Redes de Computadores

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566) e João Condeço (nº 48976)
// Abril de 2022
//----------------------------------------------------------//



#include "client_functions.h"

//Função responsável por criar o socket.
int createSocket(){
    int sockt = socket(FAMILY, SOCK_STREAM, 0);
    
    if(sockt < 0)
        printf("Socket não criado\n");
    
    printf("Socket: [ \033[0;32m OK \033[0m ]\n");

    return sockt;
}

//Função responsável por comparar duas Strings (retorna 1 se forem iguais | retorna 0 se forem diferentes)
int compareStrings(char *line1, char *line2){
    int test = 1;
    
    for (int i = 0; i < strlen(line1); i++) {
        if(line1[i] != line2[i]){
            test = 0;
        }
    }
    return test;
}

//Função responsável encontrar o server e definir a estrutura sockaddr_in
struct sockaddr_in findServer(int port, char *adress){
    struct sockaddr_in server;
    server.sin_family = FAMILY;
    server.sin_port = htons(port);
        
    if(inet_pton(FAMILY, adress, &server.sin_addr) <= 0){
        printf("Server não funciona\n");
        exit(0);
    }
    
    printf("Server: [ \033[0;32m OK \033[0m ]\n");
    return server;
}


//Função onde ocorre o funcionamento principal do cliente
void runClient(const char *name, int port){
    char bf[1024];
    int maxDescriptor;
    bzero(bf, 1024);
    memset(bf, 0, sizeof(bf));
    
    //obtenção do endereço I.P. do server
    struct hostent *host = gethostbyname(name);
    if(!host){
        printf("HOST: [ \033[0;31m NOT FOUND \033[0m ]\n");
        exit(0);
    }
    
    char *adress = inet_ntoa(*(struct in_addr*)host->h_addr);
    printf("HOST: [ \033[0;32m FOUND \033[0m ]\n");
    
    //Criação do socket
    int sockt = createSocket();
    
    //setup da estrutura associada ao server
    struct sockaddr_in server = findServer(port, adress);
    
    //Recolha do username (à escolha do utilizador)
    bzero(username, 1024);
    memset(username, 0, sizeof(username));
    printf("\nUsername: ");
    fgets(username, 1024, stdin);
    printf("\n");
    username[strcspn(username, "\n")] = 0;
    
    //Efetuar conexão com o servidor
    if(connect(sockt, (struct sockaddr *)&server, sizeof(server)) < 0){
        printf("\nCONNECTION: [ \033[0;31m FAILED \033[0m ]\n");
        exit(1);
    }
    
    //Enviar para o servidor o username previamente escolhido
    send(sockt, username, strlen(username), 0);
    
    //Criação do set que irá conter o fd do cliente e o stdin
    fd_set read_fds;
    int active, w;
    
    while(true){
        FD_ZERO(&read_fds);
        FD_SET(sockt, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        maxDescriptor = STDIN_FILENO;
           
        if(sockt>maxDescriptor) maxDescriptor = sockt;
        
        active = select((sockt+1), &read_fds, NULL, NULL, NULL);
           
        if(active == -1){
            perror("SELECT FAILED");
            exit(1);
        }
        
        //Caso hajam mensagens enviadas pelo servidor
        if(FD_ISSET(sockt, &read_fds)){
            bzero(bf, 1024);
            memset(bf, 0, sizeof(bf));
            
            w = read(sockt, bf, 1024);
            if(w < 0){
                perror("READING FAILED");
                exit(1);
            }
            if(!w){
                printf("CONNECTION: [ \033[0;31m Severed by the server \033[0m ]\n");
                break;
            }
            
            printf("%s\n", bf);
        }
        
        //Caso haja mensagens a enviar para o servidor
        if(FD_ISSET(0, &read_fds)){
            bzero(bf, 1024);
            memset(bf, 0, sizeof(bf));
            
            fgets(bf, 1024, stdin);
            
            w = send(sockt, bf, strlen(bf), 0);
            printf("\033[0;32m-You\033[0m\n\n");    //Indica que foi o user a enviar a mensagem
            
            if(w < 0){
                perror("SENDING FAILED");
                exit(1);
            }
            
            //Se a string inserida for QUIT então a conexão é terminada e o programa termina
            if(compareStrings(bf, "QUIT\n")){
                break;
            }
        }
    }
    close(sockt);
}
