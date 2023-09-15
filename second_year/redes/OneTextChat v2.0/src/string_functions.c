#include "string_functions.h"

// => Função responsável por comparar duas Strings (retorna 1 se forem iguais | retorna 0 se forem diferentes)
int compareStrings(char *line1, char *line2){
    int test = 1;
    for (int i = 0; i < strlen(line1) - 1; i++) {
        if(line1[i] != line2[i]){
            test = 0;
            break;
        }
    }
    return test;
}

// => Obtém o destinatário de algo
int getDestiny(char bf[], char *str){
    int j = 0;
    char destiny[userLenght];
    bzero(destiny, sizeof(destiny));
    memset(destiny, 0, sizeof(destiny));

    //Ignora espaços antes do request
    while(((int)bf[j]) == 32 && j < userLenght){
        j++;
    }
    
    //Ignora request
    while(((int)bf[j]) != 32 && j < userLenght){
        j++;
    }
    
    //Ignora espaço entre request e destino
    while(((int)bf[j]) == 32 && j < userLenght){
        j++;
    }
    int start = j;
     //Copia o nome até achar espaços
    while(((int)bf[j] != 32) && (j < userLenght)){
        destiny[j-start] = bf[j];
        j++;
    }

    return !strcmp(destiny, str);

}

// => Obtém a Tag numa "string"
char *getTag(char bf[], int lenght){
    int j = 0;
    //char fileName[lenght];
    char *fileName = (char*)calloc(lenght, sizeof(char)*lenght);
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
     //Copia o nome até achar espaços
    while(((int)bf[j] != 32 && (int)bf[j] != 10) && (j < lenght)){
        fileName[j-start] = bf[j];
        j++;
    }

    return fileName;
}

// => Verifica se o nome procurado existe e devolve a posição dele no array
int getName(char bf[], struct info sockets[]){
    char name[userLenght];
    bzero(name, sizeof(name));
    memset(name, 0, sizeof(name));
    
    strcpy(name, getTag(bf, userLenght));

    if(strlen(name) == 0) return -1;
    for(int i = 0; i < MAX_CLIENTS; i++){
        if(compareStrings(name, sockets[i].username)){
            return i;
        }
    }
    return -1;
}

// => Obtém o nome de um ficheiro (com o seu formato)
char* getFileName(char bf[]){
    char *fileDir = (char*)calloc(200, sizeof(char) * 200);
    bzero(fileDir, 200);
    memset(fileDir, 0, 200);

    strcpy(fileDir, "tags/");

    strcat(fileDir, getTag(bf, 32));
    strcat(fileDir, ".txt");
    return fileDir;
}

// => Identifica a posição no array do inicio de uma mensagem
int msgPos(char bf[], int lenght){
    int j = 0;

    //Ignora espaços antes do request
    while(((int)bf[j]) == 32 && j < lenght){
        j++;
    }
    
    //Ignora request
    while((((int)bf[j]) != 32) && j < lenght){
        j++;
    }

    //Ignora espaço entre request e fileName
    while((((int)bf[j]) == 32) && j < lenght){
        j++;
    }
    int start = j;

    //Avança o nome da tag
    while((((int)bf[j]) != 32 && ((int)bf[j]) != 10) && (j < lenght)){
        j++;
    }

    return j+1;
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

// => Obtém o tamanho de um ficheiro indicado na mensagem
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

    while(((int)bf[j] != 32  && (int)bf[j] != 10) && (j < lenght)){
        sz[j-start] = bf[j];
        j++;
    }

    return NumberToInt(sz);
}
