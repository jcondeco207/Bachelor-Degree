//----------------------------------------------------------//
// 2º Trabalho de Redes de Computadores
// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566) e João Condeço (nº 48976)
// Junho de 2022
//----------------------------------------------------------//

#include "client_functions.h"
#include <math.h>


// => Função responsável por criar o socket.
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

// => Obtém a Tag numa "string"
char *getTag(char bf[], int lenght){
    int j = 0;
    char *fileName = malloc(lenght); 
    bzero(fileName, sizeof(lenght)); 
    memset(fileName, 0, sizeof(lenght));

    //Ignora espaços antes do request
    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }
    
    //Ignora request
    while(((int)bf[j]) != 32 && j < lenght){
        j++;
    }
    
    //Ignora espaço entre request e fileName
    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }
    int start = j;
     //Copia o nome até achar espaços ou \n
    while(((int)bf[j] != 32  && (int)bf[j] != 10) && (j < lenght)){
        fileName[j-start] = bf[j];
        j++;
    }

    return fileName;
}

// => Obtém o nome de um ficheiro (com o seu formato)
char *getFileName(char bf[], int lenght){
    int j = 0;
    char *fileName = malloc(lenght); 
    bzero(fileName, sizeof(lenght)); 
    memset(fileName, 0, sizeof(lenght));

    //Ignora espaços antes do request
    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }
    
    //Ignora request
    while(((int)bf[j]) != 32 && j < lenght){
        j++;
    }
    
    //Ignora espaço entre request e fileName
    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }
    
    //ignora tag
    while(((int)bf[j]) != 32 && j < lenght){
        j++;
    }

    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }
    
    int start = j;
    
    //Copia o nome até achar espaços ou \n
    while(((int)bf[j] != 32  && (int)bf[j] != 10) && (j < lenght)){
        fileName[j-start] = bf[j];
        j++;
    }
   
    return fileName;
}

// => Calcula a potência b^e
int pow_jc(int b, int e){
    if(e == 1){
        return b;
    }
    else if(e == 0){
        return 1;
    }
    else{
        return pow_jc(b, 1) * pow_jc(b, e-1);
    }
}

// => Converte um número para int
int NumberToInt(char c[]){
    int n = 0;
    int r = 0;
    int l = strlen(c);

    for(int i = l-1; i >= 0; i--){
        n += (((int)c[i]) - 48) * pow_jc(10, r);
        r++;
    }
    return n;
}

// => Obtém o tamanho de um ficheiro indicado numa string
int fileSZ(char bf[], int lenght){
    int j = 0;
    char *sz = malloc(lenght); 
    bzero(sz, sizeof(lenght)); 
    memset(sz, 0, sizeof(lenght));

    //Ignora espaços antes do request
    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }

    //Ignora request
    while(((int)bf[j]) != 32 && j < lenght){
        j++;
    }

    //Ignora espaço entre request e fileName
    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }

    //ignora tag
    while(((int)bf[j]) != 32 && j < lenght){
        j++;
    }

    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }

    while(((int)bf[j]) != 32 && j < lenght){
        j++;
    }

    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }

    int start = j;

    //Copia o nome até achar espaços ou \n
    while(((int)bf[j] != 32  && (int)bf[j] != 10) && (j < lenght)){
        sz[j-start] = bf[j];
        j++;
    }

    return NumberToInt(sz);
}

// => Converte um int para o respetivo char (em formato "string")
char *toChar(int n){
    if(n == 0){
        return "0";
    }
    char aux;
    int i = floor(log10(abs(n))) + 1;
    char *number = (char *)calloc(i, sizeof(char));
    do{
        i--;
        aux = (n % 10) + '0';
        number[i] = aux;
        n /= 10;
    }while(n != 0);

    return number;
}

// => Interpreta as mensagens do servidor relativamente a nomes de utilizador
int getMsg(char bf[]){
    int j = 1;
    char msg[5];
    bzero(msg, sizeof(msg));
    memset(msg, 0, sizeof(msg));
    
    //Avança até achar a primeira mensagem
    while(((int)bf[j]) == 32 && j < 5){
        j++;
    }
    j = j - 1;

    int start = j;
    //Copia a mensagem até achar espaços
    while(((int)bf[j] != 32) && (j < 5)){
        msg[j-start] = bf[j];
        j++;
    }

    if(strlen(msg) == 0) return -1;
    for(int i = 0; i < 2; i++){
        if(compareStrings(msg, "OK")){
            return true;
        }
        else if(compareStrings(msg, "ERR")){
            return false;
        }
    }
    return false;
}

// => Transfere o conteúdo de uma lista para um array
char* intoArray(List L, int sz, int nlines){
    Position P = Header(L);
    P = Advance(P);
    char *content = (char*)calloc(sz,sizeof(char)*sz);
    
    bzero(content, strlen(content));
    memset(content, 0, strlen(content));

    while(!IsLast(P, L)){
        strcat(content, Retrieve(P));
        strcat(content, "\n");
        P = Advance(P);
    }

    strcat(content, Retrieve(P));
    
    return content;
}

// => Função responsável encontrar o server e definir a estrutura sockaddr_in
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

// => Identifica qual o pedido
int requestValue(char bf[]){
    int j = 1;
    char request[8];
    bzero(request, sizeof(request));
    memset(request, 0, sizeof(request));
    int pos = strcspn(bf, "\n");
    bf[strcspn(bf, "\n")] = 0;
    
    //Avança até achar a primeira mensagem
    while(((int)bf[j]) == 32 && j < 8){
        j++;
    }
    j = j - 1;

    int start = j;
    //Copia a mensagem até achar espaços
    while(((int)bf[j] != 32) && (j < 8)){
        request[j-start] = bf[j];
        j++;
    }

    if(strlen(request) == 0) return -1;

    if(!strcmp(request, "MSG")){
        bf[pos] = '\n';
        return 1;
    }
    else if(!strcmp(request, "POST")){
        bf[pos] = '\n'; 
        return 2;
    }
    else if(!strcmp(request, "READ")){
        bf[pos] = '\n'; 
        return 3;
    }
    else if(!strcmp(request, "ONLINE")){
        bf[pos] = '\n'; 
        return 4;
    }
    else if(!strcmp(request, "FILE")){
        bf[pos] = '\n'; 
        return 5;
    }
    else if(!strcmp(request, "STICKER")){
        bf[pos] = '\n'; 
        return 6;
    }
    else if(!strcmp(request, "RMV")){
        bf[pos] = '\n'; 
        return 7;
    }
    else if(!strcmp(request, "ADD")){
        bf[pos] = '\n'; 
        return 8;
    }
    return -1;
}

// => Função onde ocorre o funcionamento principal do cliente
void runClient(const char *name, int port){
    int sockt;
    char bf[1024];
    int maxDescriptor;
    char option[5];
    char username[1024];
    
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
    
    
    // => Recolha do username (à escolha do utilizador)
    while(true){
        // => Criação do socket
        sockt = createSocket();
    
        // => setup da estrutura associada ao server
        struct sockaddr_in server = findServer(port, adress);

        bzero(username, 1024);
        memset(username, 0, sizeof(username));
        printf("\nUsername: ");
        fgets(username, 1024, stdin);
        printf("\n");
        username[strcspn(username, "\n")] = 0;
        
        // => Efetuar conexão com o servidor
        int c = connect(sockt, (struct sockaddr *)&server, sizeof(server));
        if(c < 0){
            printf("\nCONNECTION: [ \033[0;31m FAILED \033[0m ]\n");
            exit(1);
        }
        
        // => Enviar para o servidor o username previamente escolhido
        send(sockt, username, strlen(username), 0);
        bzero(bf, 1024);
        memset(bf, 0, sizeof(bf));
        read(sockt, bf, 1024);
        printf("%s", bf);

        // => Se o username for aceite continua
        if(getMsg(bf)){
            break;
        }
        // => Se o username for recusado são apresentadas as opções
        else{
            close(sockt);
            printf("O utilizador já existe. Deseja tentar novamente?\n  \t 0 -> Não | 1-> Sim\n");
            fgets(option,5,stdin);
            if(compareStrings(option,"0\n")){return;}
        }
        bzero(bf, 1024);
        memset(bf, 0, sizeof(bf));
    }

    bzero(bf, 1024);
    memset(bf, 0, sizeof(bf));

    //Criação do set que irá conter o fd do cliente e o stdin
    fd_set read_fds;
    int active, w;
    int mode = 0; // 0 -> Enviar para o servidor | 1 -> Criar post | 2 -> Envio de Ficheiros
    int nlines;
    int sz;
    int skip; 
    char* tag = (char*)calloc(32, sizeof(char));
    List post = MakeEmpty(NULL);
    char* firstLine = (char*)calloc(50,sizeof(char)*50);
    
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
        
        // => Caso hajam mensagens enviadas pelo servidor
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
            
            // => Se tiver a receber um ficheiro (em formato binário)
            if(requestValue(bf) == 5){
                int size = fileSZ(bf, 50);
                int binaryContent[size]; 
                char fileName[32];
                bzero(fileName, 32);
                memset(fileName, 0, sizeof(fileName));
                strcpy(fileName, getFileName(bf, 32));
                recv(sockt, binaryContent, size,0);
                sleep(1);
                
                FILE *myf;
                myf = fopen(fileName, "wb");

                if(myf == NULL){
                    printf("ERR FILE\n");
                }

                else{
                    fwrite(binaryContent, sizeof(int), size, myf);
                    fclose(myf);
                }
            }
        }
        
        // => Caso haja mensagens a enviar para o servidor
        if(FD_ISSET(0, &read_fds)){
            bzero(bf, 1024);
            memset(bf, 0, sizeof(bf));
            fgets(bf, 1024, stdin);

            // => Prepara o programa para escrever um POST
            if(requestValue(bf) == 2){
                mode = 1;
                post = MakeEmpty(NULL);
                nlines = 0;
                sz = 0;
                skip = 1;
                
                bzero(firstLine, 50);
                memset(firstLine, 0, 50);
                
                strcpy(firstLine, "POST ");
                strcat(firstLine, getTag(bf, 32));
                strcat(firstLine, "\n");

                Insert(firstLine, post);
                                
                bzero(firstLine, 50);
                memset(firstLine, 0, 50);

                bzero(tag, 32);
                memset(tag, 0, strlen(tag));
                strcpy(tag, getTag(bf, 32));
            }
            // => Mostra os utilizadores online
            else if(requestValue(bf) == 4){
                printf("Utilizadores Online:\n");
            }
            // => Entra no modo de envio de ficheiros
            else if(requestValue(bf) == 5){
                mode = 2;
                
            }
            
            // => Envio de mensagens
            if(mode == 0){
                w = send(sockt, bf, strlen(bf), 0);
                if(requestValue(bf) == 1) printf("\033[0;32m-You\033[0m\n\n");    //Indica que foi o user a enviar a mensagem
                
                if(w < 0){
                    perror("SENDING FAILED");
                    exit(1);
                }
                
                //Se a string inserida for QUIT então a conexão é terminada e o programa termina
                if(compareStrings(bf, "QUIT\n")){
                    break;
                } 
            }

            // => Envio de Posts
            else if(mode == 1){
                
                if(compareStrings(bf,"EXIT") && nlines > 0){
                    printf("\n");
                    mode = 0;
                    //P = Header(post);
                    char toSend[sz*2];
                    strcpy(toSend, intoArray(post, sz, nlines));
                    w = send(sockt, toSend, strlen(toSend), 0);
                    
                    if(w < 0){
                        perror("SENDING FAILED");
                        exit(1);
                    }
                    post = MakeEmpty(post);
                    nlines = 0;
                    sz = 0;
                }
                else{
                    if(skip == 0){
                        Insert(bf, post);

                        nlines++;
                        sz += strlen(bf); 
                    }
                    skip = 0;
                }
                bzero(bf, strlen(bf));
                memset(bf, 0, strlen(bf));
            }

            // => Envio de ficheiros
            else if(mode == 2){
                char fileName[32];

                bzero(fileName, 32);
                memset(fileName, 0, 32);

                strcpy(fileName, getFileName(bf, 32));

                FILE *myf;
                myf = fopen(fileName, "rb");

                if(myf == NULL){
                    printf("ERR FILE\n");
                }
                else{
                    fseek(myf, 0, SEEK_END);
                    int lenght = ftell(myf);
                    fseek(myf, 0, SEEK_SET);
                                    
                    int fileContent[lenght];
                    fread(&fileContent, lenght + 1, sizeof(int), myf);
                                    
                    fclose(myf);
                    bf[strcspn(bf, "\n")] = 0;
                    strcat(bf, " ");
                    strcat(bf, toChar(lenght));
                    w = send(sockt, bf, strlen(bf), 0);
                    for(int i = 0; i < 20000000; i++){}
                    write(sockt, fileContent, sizeof(fileContent));
                    sleep(1);
                }
                mode = 0;
            }
        }
    }
    close(sockt);
}
