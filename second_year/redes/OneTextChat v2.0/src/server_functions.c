//----------------------------------------------------------//
// 2º Trabalho de Redes de Computadores

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566) e João Condeço (nº 48976)
// Junho de 2022
//----------------------------------------------------------//

#include "server_functions.h"

// => Função responsável por criar o socket.
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

// => Setup da estrutura sockaddr_in
struct sockaddr_in setUpAdress(){
    struct sockaddr_in address;
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    return address;              
}

// => Gerir uma nova conexão
int newConnections(int sockt, struct sockaddr_in address){
    int new_socket;
    int addrsz = sizeof(address);
    
    if((new_socket = accept(sockt, (struct sockaddr *)&address,(socklen_t*)&addrsz))<0){
        perror("Accept failed");
    }

    printf("Nova conexão, o FD do socket é %d , o ip é : %s  e a porta : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
    
    return new_socket;
}

// => Envia mensagem de Boas Vindas aos  novos utilizadores
void greetings(int sockt, struct sockaddr_in address){
    char *message = "Status: [ \033[0;32m Connected \033[0m ]\n\n|---- Welcome to \033[0;36m1TextChat\033[0m ----|\n";

    if(send(sockt, message, strlen(message), 0) != strlen(message)){
        perror("Message");
    }
}

// => Função responsável por comparar duas Strings (retorna 1 se forem iguais | retorna 0 se forem diferentes)
int compareUsers(char *line1, char *line2){
    if(strlen(line1) != strlen(line2)){return 0;}
    int test = 1;
    for (int i = 0; i < strlen(line1); i++) {
        if(line1[i] != line2[i]){
            test = 0;
        }
    }
    return test;
}

// => Verifica se um ficheiro existe
int fileExists(char* fileName){
    FILE *myf;
    int exists = true;
    myf = fopen(fileName, "r");
    
    if(myf == NULL){
        exists = false;
    }
    else{
        fclose(myf);
    }
    
    return exists;
}

/**
* => Procura o username
* => Se o encontrar devolve true
* => Se não encontrar devolve false
*/
int userFound(char* user, struct info sockets[]){
    int found = true;
    
    for(int i = 0; i < MAX_CLIENTS; i++){
        found = compareUsers(user, sockets[i].username);
        if(found == true && sockets[i].num != 0) return false;
    }
    return true;
}


// => Escreve nos ficheiros associados às tags os novos Posts
void sendPOST(char* tagName, char* post, char* sender){
    char fileName[250] = "tags/";

    strcat(fileName, tagName);
    fileName[strcspn(fileName, "\n")] = 0;
    strcat(fileName, ".txt");

    FILE *myf;
    myf = fopen(fileName, "a");
    if(myf == NULL){
        printf("A tag à qual %s está a tentar adicionar conteúdo não existe.\n", sender);
        return;
    }
    fprintf(myf, "\n ");
    fprintf(myf, "\n%s", post);
    fprintf(myf, "\n-%s", sender);  
    fclose(myf);
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

// => Envia o conteúdo de uma tag para o cliente
void readFile(char* fileName, int socket){
    FILE *myf;
    myf = fopen(fileName, "r");
    int i = 0;

    if (myf == NULL) {
        printf("\nFicheiro indisponível.\n\n");
        exit(1);
    }
    else{
        char *line = malloc(1024);
        fgets(line, 1024, myf);

        while(1){
            bzero(line, 1024);
            memset(line, 0, 1024);
            line[strcspn(line, "\n")] = 0;
            if(fgets(line, 1024, myf) == NULL) break;
            if(requestValue(line) == 2){
                bzero(line, 1024);
                memset(line, 0, 1024);
                i++;
                strcat(line, "POST ");
                strcat(line, toChar(i));
                strcat(line, "\n");                
            }
            else{strcat(line, "\n");}
            send(socket, line, strlen(line), 0);
        }
        free(line);
   }
   fclose(myf);
}

// => Verifica se o client em questão é admin da tag indicada
int isAdmin(struct info admin, char *file){
    FILE *myf;
    myf = fopen(file, "r");
    char *line = malloc(1024);
    if(myf == NULL){
        printf("\nFicheiro indisponível.\n\n");
        return false;
    }
    else{
        bzero(line, 1024);
        memset(line, 0, 1024);
        fscanf(myf, "%[^\n]%*c", line);
    }

    if(compareStrings(admin.username, line)){
        return true;
    }
    else{
        send(admin.num, "Não tem permissões para adicionar utilizadores\n", 51, 0);
        return false;
    }
    
}

// => Devolve o nome de um ficheiro sem a sua extensão
// => Por exemplo: "GLOBAL.txt" -> "GLOBAL"
char* rmvTXT(char* fileName){
    char* tag = (char*)calloc(tagLenght, sizeof(char)*tagLenght);
    int j = 0;
    
    while((fileName[j] != '.') && fileName[j] != '\0'){
        j++;
    }
    
    for(int i = 0; i < j; i++){
        tag[i] = fileName[i];
    }

    return tag;
}

// => Verifica se "name" é admin da tag "fileName"
// => Para tal verifica a primeira linha do ficheiro associado à tag
int belongs(char* name, char* fileName){
    FILE *myf;
    char *location = (char*)calloc((tagLenght + 5), sizeof(char)*(tagLenght + 5));
    strcpy(location, "tags/");
    strcat(location, fileName);
    
    myf = fopen(location, "r");
    if(myf == NULL){
        return 0;
    }
    char* line = (char*)calloc(userLenght, sizeof(char)*userLenght);
    fgets(line, userLenght, myf);
    line[strcspn(line, "\n")] = 0;
    
    if(strlen(line) < strlen(name)){
        return 0;
    }
    return !strcmp(name, line);
}

// => Adiciona à struct de um utilizador as tags à qual este é admin
void addTags(struct info user){
    DIR *folder;
    struct dirent *dir;
    folder = opendir("./tags");
    if(folder){
        while((dir = readdir(folder))!=NULL){
            if(belongs(user.username, dir->d_name)){
                Insert(rmvTXT(dir->d_name), user.tags);
            }
        }
        closedir(folder);
    }
}

// => Encontra o socket ao qual "name" está associado
int findSocket(struct info sockets[], char *name){
    for(int i = 0; i < MAX_CLIENTS; i++){
        if(compareUsers(sockets[i].username, name)){
            return i;
        }
    }
    return -1;
}

// => Identifica o membro a ser adicionado/removido de uma Tag
char *getNewMember(char *bf){
    int j = msgPos(bf, tagLenght);
    char *username = (char*)calloc(10, sizeof(char) * 10);
    bzero(username, sizeof(userLenght));
    memset(username, 0, userLenght);

    for(int i = 0; (i < userLenght && j < strlen(bf)); i++){
        username[i] = bf[j];
        j++;
    }
    return username;
}

// => Verifica se o nome em questão está associado a um utilizador ativo
int isUser(char bf[], struct info sockets[]){
    for(int i = 0; i < MAX_CLIENTS; i++){
        if(sockets[i].num != 0 && getDestiny(bf, sockets[i].username)){
            return 1;
        }
    }
    return 0;
}

// => Retorna o socket ao qual o nome em bf está associado
int userSockt(char bf[], struct info sockets[]){
    for(int i = 0; i < MAX_CLIENTS; i++){
        if(sockets[i].num != 0 && getDestiny(bf, sockets[i].username)){
            return i;
        }
    }
    return 0;
}


// => Função que gere o funcionamento principal
int runServer(){
    struct info sockets[MAX_CLIENTS];
    char bf[1024];
    char *notFound = "\033[0;31mUtilizador não existe.\033[0m\n";
    char ok[1024] = "OK ";
    char err[1024] = "ERR ";

    int socketD;
    int maxDescriptor;
    int activeSocket;
    int new_socket;
    int wasRead;

    // => Aloca o espaço na memória para os usernames
    for(int i = 0; i < MAX_CLIENTS; i++){
        sockets[i].username = (char*) malloc((userLenght + 1)*sizeof(char));
        sockets[i].tags = MakeEmpty(NULL);
    }

    
    int sockt = createSocket();
    struct sockaddr_in address = setUpAdress();
    
    if(bind(sockt, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    int addrsz = sizeof(address);
    
    // => Iniciar espera por conexões
    if (listen(sockt, 10) < 0) { // 10 -> fila de espera do listen -> 1/3 dos num max de clientes
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    fd_set readfds;
    
    // => Inicializa todos os clientes a zero
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
        
        // => Se houverem novas conexões
        if(FD_ISSET(sockt , &readfds)){
            new_socket = newConnections(sockt, address);
            
            // => Os novos clientes são adicionados no array
            // => Apenas se o username não for repetido
            for(int i = 0; i < MAX_CLIENTS; i++){
                if(sockets[i].num == 0){
                    sockets[i].num = new_socket;
                    bzero(bf, sizeof(bf));
                    memset(bf, 0, 1024);
                    
                    read(sockets[i].num, bf, sizeof(bf));
                    bf[strcspn(bf, "\n")] = 0;

                    if(userFound(bf, sockets)){
                        strcpy(sockets[i].username, bf);
                        strcat(ok, bf);
                        strcat(ok, "\n");
                        send(sockets[i].num, ok, strlen(ok), 0);
                        
                        bzero(ok, sizeof(ok));
                        memset(ok, 0, 1024);
                        strcpy(ok, "OK ");

                        Insert("GLOBAL", sockets[i].tags);
                        addTags(sockets[i]);
                        greetings(sockets[i].num, address);
                    }

                    else{
                        strcat(err, bf);
                        strcat(err, "\n");
                        send(sockets[i].num, err, strlen(err), 0);

                        bzero(err, sizeof(err));
                        memset(err, 0, 1024);
                        strcpy(err, "ERR ");
                        
                        sockets[i].num = 0;                    
                    }
                  
                    bzero(bf, sizeof(bf));
                    memset(bf, 0, 1024);

                    break;
                }
            }
        }
        
        // => Caso contrário é analizado o pedido
        for (int i = 0; i < MAX_CLIENTS ; i++){
            bzero(bf, sizeof(bf));
            memset(bf, 0, 1024);
            socketD = sockets[i].num;
            
            //É feito o teste ao socket em questão
            if(FD_ISSET(socketD, &readfds)){
                wasRead = read(socketD, bf, sizeof(bf));    //Ler o valor recebido

                // => Quando o <user> sai do chat
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
                    bzero(sockets[i].username, sizeof(userLenght));
                    sockets[i].tags = MakeEmpty(sockets[i].tags);
                }
                // => Se for MSG
                else if(requestValue(bf) == 1){
                    bf[strcspn(bf, "\n")] = 0;

                    // => Quando o <user> envia uma mensagem para todos (MSG Destino Conteúdo)
                    if(getDestiny(bf, "GLOBAL")){
                        printf("%s enviou '%s' para todos\n", sockets[i].username, bf);
                        strcat(bf,"\n\033[0;32m-");
                        strcat(bf, sockets[i].username);
                        strcat(bf,"\n\n\033[0m");

                        for(int j = 0; j < MAX_CLIENTS; j++){
                            if(j!=i && sockets[j].num != 0){
                                send(sockets[j].num, bf, strlen(bf), 0);
                            }
                        }
                        send(sockets[i].num, "OK MSG GLOBAL\n", 16, 0);
                    }

                    // => Caso seja uma mensagem privada para um utilizador
                    // => É procurado o socket do destino
                    else if(isUser(bf, sockets) > 0){
                        int s = userSockt(bf, sockets);
                        if(s >= 0) printf("%s enviou '%s' para %s\n", sockets[i].username, bf, sockets[s].username);
                        else printf("%s tentou enviar '%s', mas o utilizador não existe\n", sockets[i].username, bf);
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

                    // => Caso contrário será para os membros de uma Tag
                    else{                  
                        char dir[200];
                        char tagName[200];
                        bzero(dir, 200);
                        memset(dir, 0, 200);
                        bzero(tagName, 200);
                        memset(tagName, 0, 200);
                        strcpy(dir, getFileName(bf));  
                        strcpy(tagName, getTag(bf, tagLenght));

                        // => Se a Tag existir será enviada a mensagem para todos os membros
                        // => (Se o utilizador em questão for membro da mesma)
                        if(fileExists(dir) && existsTag(tagName, sockets[i].tags)){
                            strcat(bf,"\n\033[0;32m-");
                            strcat(bf, sockets[i].username);
                            strcat(bf,"\n\n\033[0m"); 
                            for(int j = 0; j < MAX_CLIENTS; j++){
                                if(j!=i && sockets[j].num != 0 && existsTag(tagName, sockets[j].tags)){
                                    send(sockets[j].num, bf, strlen(bf), 0);

                                }
                            }
                        }

                        // => Se a Tag em questão não existir será criada
                        // => O utilizador torna-se administrador da nova Tag
                        else if(!fileExists(dir)){
                            FILE *myf;
                            myf = fopen(dir, "w");
                            fprintf(myf, "%s", sockets[i].username);   
                            fclose(myf);
                            printf("Tag %s criada por %s\n", getTag(bf, tagLenght), sockets[i].username);
                            Insert(getTag(bf, tagLenght) , sockets[i].tags);
                        }

                    }
                }

                // => Se for POST
                /** Formato:
                  * "POST DESTINO
                  *  Linha 1 com conteúdo
                  *  Linha 2 com conteúdo
                  *  ...................."
                  *  Qualquer conteúdo para além de "POST DESTINO" na 
                  *  primeira linha será ignorado
                */
                else if(requestValue(bf) == 2){
                    char dir[200];
                    bzero(dir, 200);
                    memset(dir, 0, 200);
                    strcpy(dir, getFileName(bf));
                        printf("%s\n", dir); 
                    char tagName[200];
                    bzero(tagName, 200);
                    memset(tagName, 0, 200);
                    strcpy(tagName, getTag(bf, tagLenght));

                    // => Se a Tag não existir será criada tal como nas MSG
                    if(!fileExists(dir)){
                        FILE *myf;
                        myf = fopen(dir, "w");
                        fprintf(myf, "%s", sockets[i].username);   
                        fclose(myf);
                        printf("Tag %s criada por %s\n", tagName, sockets[i].username);
                        Insert(tagName, sockets[i].tags);
                    }
                    if(existsTag(tagName, sockets[i].tags)){
                        sendPOST(tagName, bf, sockets[i].username);
                        for(int j = 0; j < MAX_CLIENTS; j++){
                            if(sockets[j].num > 0 && (j!=i) && existsTag(tagName, sockets[j].tags)){
                                char newPost[50];
                                bzero(newPost, 32);
                                memset(newPost, 0, 32);
                                strcat(newPost, "Recebeu um novo post na tag: ");
                                strcat(newPost, tagName);
                                strcat(newPost, "\n");
                                send(sockets[j].num, newPost, strlen(newPost), 0);
                            }
                        } 
                        send(sockets[i].num, "OK POST\n", 9, 0);
                    }    

                    else{
                        send(sockets[i].num, "ERR POST\n", 10, 0);
                    }
                    
                }

                // => Se for READ (Formato: READ TAG)
                // => Apresenta o conteúdo de uma Tag
                else if(requestValue(bf) == 3){
                    bf[strcspn(bf, "\n")] = 0;
                    char dir[200];
                    char tagName[200];
                    bzero(dir, 200);
                    memset(dir, 0, 200);
                    bzero(tagName, 200);
                    memset(tagName, 0, 200);
                    strcpy(dir, getFileName(bf));  
                    strcpy(tagName, getTag(bf, tagLenght));

                    //1º verificar privilégios 
                    if(existsTag(tagName, sockets[i].tags)){
                        char ok_read[20];
                        bzero(ok_read, 20);
                        memset(ok_read, 0, 20);
                        strcat(ok_read, "OK ALLPOSTS ");
                        strcat(ok_read, tagName);
                        strcat(ok_read, "\n");
                        send(sockets[i].num, ok_read, strlen(ok_read), 0);
                        readFile(dir, sockets[i].num);
                    }
                    else{
                        char err_read[20];
                        bzero(err_read, 20);
                        memset(err_read, 0, 20);
                        strcat(err_read, "ERR ALLPOSTS ");
                        strcat(err_read, tagName);
                        strcat(err_read, "\n");
                        send(sockets[i].num, err_read, strlen(err_read), 0);
                    }
                }

                // => Se for ONLINE
                // => Apresenta os utilizadores que estão online
                else if(requestValue(bf) == 4){
                    bf[strcspn(bf, "\n")] = 0;
                    for(int j = 0; j < MAX_CLIENTS; j++){
                        char online[userLenght];
                        bzero(online, userLenght);
                        memset(online, 0, userLenght);
                        if(j != i && strlen(sockets[j].username) > 0){
                            strcpy(online, sockets[j].username);
                            strcat(online, "\n");
                            send(sockets[i].num, online, strlen(online), 0);
                        }
                    }
                }

                // => Se for FILE (Formato: FILE DEST SIZE)
                // => Apenas de utilizadores para utilizadores
                else if(requestValue(bf) == 5){
                    bf[strcspn(bf, "\n")] = 0;
                    if(isUser(bf, sockets) > 0){
                        int s = userSockt(bf, sockets);
                        strcat(bf,"\n\033[0;32m-");
                        strcat(bf, sockets[i].username);
                        strcat(bf,"\n\n\033[0m");
                        if(s != -1){
                            send(sockets[s].num, bf, strlen(bf), 0);
                            int size = fileSZ(bf, 50);
                            int data[size];
                            if(s >= 0) printf("%s enviou um ficheiro de %d bytes para %s\n", sockets[i].username, size, sockets[s].username);
                            else printf("%s tentou enviar um ficheiro, mas o utilizador não existe\n", sockets[i].username);
                            bzero(data, sizeof(data));
                            memset(data, 0, size);
                            recv(sockets[i].num, data, sizeof(data), 0);
                            // => Dá tempo suficiente para os dados todos chegarem
                            for(int i = 0; i < 10000000; i++){}
                            printf("\n");
                            write(sockets[s].num, data, sizeof(data));
                            sleep(1);
                            bzero(bf, sizeof(bf));
                            memset(bf, 0, 1024);
                        }
                        else{
                            send(sockets[i].num, notFound, strlen(notFound), 0);
                        }
                    }
                }

                // => Se for RMV (Formato: RMV TAG USER)
                // => O administrador remove um utilizador de uma Tag
                else if(requestValue(bf) == 7 && isAdmin(sockets[i], getFileName(bf))){
                    bf[strcspn(bf, "\n")] = 0;
                    int toRemove = findSocket(sockets, getNewMember(bf));
                    if(toRemove >= 0){
                        Delete(getTag(bf, tagLenght) , sockets[toRemove].tags);
                        char msg[200] = "Foi removido da tag ";
                        strcat(msg, getTag(bf, tagLenght));
                        strcat(msg, "\n");
                        send(sockets[toRemove].num, msg, strlen(msg), 0);
                    }
                    else{
                        send(sockets[i].num, "Utilizador não encontrado\n", 29, 0);
                    }
                }    

                // => Se for ADD (Formato: ADD TAG USER)
                // => O administrador adiciona um utilizador a uma Tag
                else if(requestValue(bf) == 8 && isAdmin(sockets[i], getFileName(bf))){ 
                    bf[strcspn(bf, "\n")] = 0;
                    int newMember = findSocket(sockets, getNewMember(bf));
                    if(newMember >= 0){
                        Insert(getTag(bf, tagLenght) , sockets[newMember].tags);
                        char msg[200] = "Foi adicionado à tag ";
                        strcat(msg, getTag(bf, tagLenght));
                        strcat(msg, "\n");
                        send(sockets[newMember].num, msg, strlen(msg), 0);
                    }
                    else{
                        send(sockets[i].num, "Utilizador não encontrado\n", 29, 0);
                    }
                }
                
                bzero(bf, sizeof(bf));
                memset(bf, 0, 1024);
            }
        }
    }
    return 1;
}

