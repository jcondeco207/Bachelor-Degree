//----------------------------------------------------------//
// 1º Trabalho de Redes de Computadores

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566) e João Condeço (nº 48976)
// Abril de 2022
//----------------------------------------------------------//

#include "server_functions.h"

//Função responsável por criar o socket.
int createSocket(){
    int opt = 1;

    int sockt = socket(FAMILY, SOCK_STREAM, 0);

    if(sockt < 0)
        printf("Socket não criado\n");
    
    if(setsockopt(sockt, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
       perror("setsocket");
       exit(EXIT_FAILURE);
    }

    printf("Socket: [ \033[0;32m OK \033[0m ]\n");

    return sockt;
}

//Setup da estrutura sockaddr_in
struct sockaddr_in setUpAdress(){
    struct sockaddr_in address;
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    return address;              
}

//gerir uma nova conexão
int newConnections(int sockt, struct sockaddr_in address){
    int new_socket;
    int addrsz = sizeof(address);
    char *message = "Status: [ \033[0;32m Connected \033[0m ]\n\n|---- Welcome to \033[0;36m1TextChat\033[0m ----|\n";
    
    if((new_socket = accept(sockt, (struct sockaddr *)&address,(socklen_t*)&addrsz))<0){
        perror("Accept failed");
    }
    
    printf("Nova conexão, o FD do socket é %d , o ip é : %s  e a porta : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
    
    if(send(new_socket, message, strlen(message), 0) != strlen(message)){
        perror("Message");
    }
    
    return new_socket;
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

//Verifica se o nome procurado existe e devolve a posição dele no array

int getName(char bf[], struct info sockets[]){
    int j = 1;
    char name[userLenght];
    bzero(name, sizeof(name));
    memset(name, 0, sizeof(name));
    
    //Avança até achar o primeiro nome
    while(((int)bf[j]) == 32 && j < userLenght){
        j++;
    }
    
    int start = j;
    
    //Copia o nome até achar espaços
    while(((int)bf[j] != 32) && (j < userLenght)){
        name[j-start] = bf[j];
        j++;
    }
    if(strlen(name) == 0) return -1;
    for(int i = 0; i < MAX_CLIENTS; i++){
        if(compareStrings(name, sockets[i].username)){
            return i;
        }
    }
    return -1;
}

//Função que gere o funcionamento principal
int runServer(){
    struct info sockets[MAX_CLIENTS];
    char bf[1024];
    char *notFound = "\033[0;31mUtilizador não existe.\033[0m\n";
    int socketD;
    int maxDescriptor;
    int activeSocket;
    int new_socket;
    int wasRead;
    
    //Aloca o espaço na memória para os usernames
    for(int i = 0; i < MAX_CLIENTS; i++){
        sockets[i].username = (char*) malloc((userLenght + 1)*sizeof(char));
    }
    
    
    int sockt = createSocket();
    struct sockaddr_in address = setUpAdress();
    
    if(bind(sockt, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    int addrsz = sizeof(address);
    
    //Iniciar espera por conexões
    if (listen(sockt, 10) < 0) { // 10 -> fila de espera do listen -> 1/3 dos num max de clientes
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    fd_set readfds;
    
    //Inicializa todos os clientes a zero
    for(int i = 0; i < MAX_CLIENTS; i++){
        sockets[i].num = 0;
        bzero(sockets[i].username, sizeof(userLenght));
        memset(sockets[i].username, 0, userLenght);
    }
    
    
    while(true){
        FD_ZERO(&readfds);
        FD_SET(sockt, &readfds);
        maxDescriptor = sockt;
        
        for(int i = 0; i < MAX_CLIENTS; i++){
            socketD =  sockets[i].num;
            if(socketD > 0)
                FD_SET(socketD, &readfds);
            
            if(socketD > maxDescriptor)
                maxDescriptor = socketD;
        }
        
        activeSocket = select(maxDescriptor + 1, &readfds, NULL, NULL, NULL);
        if((activeSocket < 0) && (errno != EINTR)){
            printf("Erro\n");
        }
        
        //Se houverem novas conexões
        if(FD_ISSET(sockt , &readfds)){
            new_socket = newConnections(sockt, address);
            
            //Os novos clientes são adicionados na lista
            for(int i = 0; i < MAX_CLIENTS; i++){
                if(sockets[i].num == 0){
                    sockets[i].num = new_socket;
                    bzero(bf, sizeof(bf));
                    memset(bf, 0, 1024);
                    
                    read(sockets[i].num, bf, sizeof(bf));
                    bf[strcspn(bf, "\n")] = 0;
                    strcpy(sockets[i].username, bf);
                  
                    bzero(bf, sizeof(bf));
                    memset(bf, 0, 1024);
                    break;
                }
            }
        }
        
        //Caso contrário
        for (int i = 0; i < MAX_CLIENTS ; i++){
            bzero(bf, sizeof(bf));
            memset(bf, 0, 1024);
            socketD = sockets[i].num;
            
            //É feito o teste ao socket em questão
            if(FD_ISSET(socketD, &readfds)){
                wasRead = read(socketD, bf, sizeof(bf));    //Ler o valor recebido
                bf[strcspn(bf, "\n")] = 0;
                
                //Quando o <user> sai do chat
                if(!wasRead){
                    printf("%s desconectou-se do servidor\n",  sockets[i].username);
                    strcat(sockets[i].username, " desligou\n");
                    
                    for(int j = 0; j < MAX_CLIENTS; j++){
                        if(j!=i)
                            send(sockets[j].num,  sockets[i].username, strlen(sockets[i].username), 0);
                    }
                    
                    close(socketD);
                    sockets[i].num  = 0;
                    memset(sockets[i].username, 0, userLenght);
                    bzero(sockets[i].username, sizeof(sockets[i].username));
                }
                
                //Quando o <user> envia uma mensagem para todos (+<mensagem>)
                else if(bf[0] == '+'){
                    printf("%s enviou '%s' para todos\n", sockets[i].username, bf);
                    
                    //Adicionar quem envia a mensagem
                    strcat(bf,"\n\033[0;32m-");
                    strcat(bf, sockets[i].username);
                    strcat(bf,"\n\n\033[0m");

                    for(int j = 0; j < MAX_CLIENTS; j++){
                        if(j!=i && sockets[j].num != 0){
                            send(sockets[j].num, bf, strlen(bf), 0);
                        }
                    }
                }
                
                //Quando o <user> envia uma mensagem para um utilizador em especifico (-<destinatário> mensagem)
                else if(bf[0] == '-'){
                    int s = getName(bf,sockets);
                    if(s >= 0) printf("%s enviou '%s' para %s\n", sockets[i].username, bf, sockets[s].username);
                    else printf("%s tentou enviar '%s', mas o utilizador não existe\n", sockets[i].username, bf);
                    
                    //Adicionar quem envia a mensagem
                    strcat(bf,"\n\033[0;32m-");
                    strcat(bf, sockets[i].username);
                    strcat(bf,"\n\n\033[0m");
                    
                    if(s != -1){
                        send(sockets[s].num, bf, strlen(bf), 0);
                    }
                    else{
                        send(sockets[i].num, notFound, strlen(notFound), 0);
                    }
                }
                bzero(bf, sizeof(bf));
                memset(bf, 0, 1024);
            }
        }
    }
    return 1;
}

