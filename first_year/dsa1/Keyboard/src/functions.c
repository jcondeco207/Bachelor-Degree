//
//  functions.c
//
//
//  Created by João and Sara Amaral on 30/05/2021.
//

#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include "hashsep.h"
#include <math.h>

#define SENTENCE_LENGHT 200

struct updates up;

//#################################################################<----- Utilities ----->######################################################################

//Retorna o valor de número em char no seu equivalente em int
long int ToNumber(char l){
    return (((int)l) - 48);
}

//Retorna o caracter inserido sem acentos em minusculas
char toLower(char l){
    if((int)l >= 65 && (int)l <= 90){
        l = (char) (((int)l) + 32);
    }
    return l;
}

//Retorna o caracter inserido com acentos em minusculas
int AccentToLower(int n){
    if(n < -96 || n > -65){
        n += 32;
    }
    return n;
}

//Retorna o tamanho de uma string
int SizeCounter(char *str){
    int counter = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        counter++;
        i++;
    }
    
    return counter;
}

//Hashing ao input do user
int NewHash(char *str, int tablesize){
    long unsigned int hashvalue = 0;
    int size = SizeCounter(str);
    while (*str != '\0') {
        hashvalue = (hashvalue << 5) + *str++;
    }
    hashvalue += size;
    return hashvalue % tablesize;
}

//Apenas para imprimir o caracter que eu quero as vezes que eu precisar
void PrintChars(int n, char c){
    for(int i = 0; i<n; i++){
        printf("%c", c);
    }
}

//Confirma se o caracter pretendido existe num array bidimensional e retorna a sua posição
int InMatrix(int values[][5], int n){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 5; j++){
            if(n == values[i][j]){
                return i;
            }
        }
    }
    return -1;
}

//#################################################################<----- Dictionary ----->######################################################################

//obtém o número correspondente a um caracter
char GetNumber(char l){
    //Indice no array + 2 = tecla correspondente
    char arr[8][4] = {  {'a', 'b', 'c'}, //tecla 2
                        {'d', 'e', 'f'}, //tecla 3
                        {'g', 'h', 'i'}, //tecla 4
                        {'j', 'k', 'l'}, //tecla 5
                        {'m', 'n', 'o'}, //tecla 6
                        {'p', 'q', 'r', 's'}, //tecla 7
                        {'t', 'u', 'v'}, //tecla 8
                        {'w', 'x', 'y', 'z'} //tecla 9
        
    };
    
    int pos = -1;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++){
            if(arr[i][j] == l){
                pos = i;
                break;
            }
        }
    }
    pos += 2;
    
    return ((char) (pos + 48));
}

//converte o valor de uma string para números e retorna o mesmo
char *RetConvert(char *word){
    char *converted = malloc(50);
    strcpy(converted, "");
    char n;
    for(int i = 0; i < strlen(word); i++){
        n = GetNumber(word[i]);
        strncat(converted, &n, 1);
    }
    return converted; 
}

//Função auxiliar para verificar os conteúdos e disposição da HashTable
void PrintTable(HashTable H){
    for(int i = 0; i <= tablesz; i++){
        Position P = H->TheLists[i]->Next;
        printf("i = %d Palavras = [ ", i);
        while(P!= NULL){
            printf("%s %d - ", P->Element, P->Freq);
            P = P->Next;
        }
        printf(" ]\n");
    }
    printf("\n");
}

//Função que gere as sugestões de palavras e formação da mensagem
void suggestions(HashTable H, char *sentence, char *in){
    int accepted = 0;
    char opt = 'n';
    char *manual = malloc(50);
    
    List L = H->TheLists[NewHash(in, H->TableSize)];
    Position P = L->Next;
    
    while(accepted ==  0 && P != NULL){
        if(!strcmp(RetConvert(normalize(P->Element)), in)){ //verifica se a palavra corresponde à sequencia de algarismos
            
            printf("Sugestão: %s, aceita (s/n)? ", P->Element);
            scanf(" %c", &opt);
            if(opt == 's'){
                break;
            }
            else if(opt == 'n'){
                P = P->Next;
            }
            else{
                printf("Opção inválida\n");
            }
        }
        
        else{
            P = P->Next;
        }
    }
    
    if(opt == 's'){
        strcat(sentence, P->Element);
    }
    else{
        printf("Não existem mais sugestões, introduza a palavra no teclado: ");
        scanf(" %s", manual);
        strcat(sentence, manual);
        Insert(manual, 0, H);
        strcpy(up.new[up.posnew], manual);
        up.posnew++;
    }
    strcat(sentence, " ");
}


//Normaliza uma frase (retira os acentos e pontuação)
char *normalize(char *str){
    char *new = malloc(50);
    strcpy(new, "");
    
    int pos;
    int i = 0;
    char temp;
    
    //strcpy(str, strlwr(str));
    int values[7][5] = {{-95 , -96 , -93, -94}, //a
                        {-89}, //c
                        {-87, -88 , -86}, //e
                        {-82, -83, -84}, //i
                        {-79}, //n
                        {-74, -75, -76, -77, -78}, //o
                        {-68, -69, -70, -71} //u
                        };

    char letters[] = {'a', 'c', 'e', 'i', 'n', 'o', 'u'};

    while(str[i] != '\0'){
        if((int)str[i] != 39){
            if((int)str[i] < 0){
                i++;
                pos = InMatrix(values, AccentToLower((int)str[i]));
                strncat(new, &letters[pos], 1);
            }
            else{
                temp = toLower(str[i]);
                strncat(new, &temp, 1);
            }
        }
        i++;
    }
    return new;
}

//Transforma o nome do ficheiro para a versão updated
char *NewName(char *name){
    char *new = malloc(100);
    strcpy(new, "");
    
    int i;
    for (i = 0; i < (strlen(name) - 4); i++) {
        strncat(new, &name[i], 1);
    }
    strcat(new, "-updated.txt");
    return new;
}

//Caso seja necessário num novo ficheiro as palavras novas + as antigas
void upload(int hf){
    char bridge[50] = "";
    
    FILE *source, *myf;
    source = fopen(up.name, "r");
    myf = fopen(NewName(up.name), "w");
    
    //Cópia
    while(1){
        if(fscanf(source," %s", bridge) == EOF) break;
        fprintf(myf,"%s\n", bridge);
    }
    
    //Palavras Novas
    if(hf){
        for (int i = 0; i < up.posnew; i++) {
            fprintf(myf,"%s,0\n", up.new[i]);
        }
    }
    else{
        for (int i = 0; i < up.posnew; i++) {
            fprintf(myf,"%s\n", up.new[i]);
        }
    }
    
    fclose(source);
    fclose(myf);
}

//#################################################################<----- Hashtable ----->######################################################################

//Converte string em int
int Value(char *numbers){
    int number = 0;
    for(int i = 0; i<strlen(numbers); i++){
        number = (number * 10) + (int)ToNumber(numbers[i]);
    }
    return number;
}

//Remove a frequencia da string e guarda-a na variável freq (referenciada pelo apontador pf)
char *TInput(char input[50], int *pf){
    char *threated = malloc(50);
    char numbers[50] = "";
    *pf = 0;
    int i = 0;
    int j = 0;
    
    for ( ; i<strlen(input) && input[i] != ','; i++) {
        
        threated[i] = input[i];
    }
    while (input[i] != '\0') {
        i++;
        numbers[j] = input[i];
        j++;
    }
    *pf = Value(numbers);
    
    return threated;
}

//Recolhe as palavras do dicionário e caso seja necessário recebe o diretório do mesmo
HashTable AddDict(HashTable H, const char *argv[], int argc, int ins, int *hf, int *loaded){
    char location[100] = "";
    char input[50] = "";
    strcpy(up.name, "");
    int freq = 0;
    int *pf = &freq;
    

    if (argc <= 1 || ins == 1) {
        printf("Insira a localização do dicionário: ");
        scanf(" %s", location);
        strcpy(up.name, location); //guarda na variável global o diretorio para mais tarde ser utilizado
    }
    else{
        for(int i = 1; i < argc; i++){
            strcat(location, argv[i]);
            strcpy(up.name, location); //guarda na variável global o diretorio para mais tarde ser utilizado
        }
    }
    
    FILE *myf;
    myf = fopen(location, "r");
    
    if (myf == NULL) {
        printf("\nFicheiro indisponível.\n\n");
        exit(1);
    }
    else{
        
        while(1){
            if(fscanf(myf," %s",input) == EOF) break;
            strcpy(input, TInput(input, pf));
            if (freq > 0) {
                *hf = 1;
            }
            Insert(input, freq, H);
            strcpy(input, "");
            *loaded = 1;
        }
    }
    fclose(myf);
    return H;
}



//#################################################################<----- Gestão ----->######################################################################

//Gere a inserção de combinações de números e chama as funções necessárias
int Receiver(HashTable H){
    up.posnew = 0;
    
    char *numbers = malloc(MAX_LENGHT);
    char *sentence = malloc(SENTENCE_LENGHT);
    strcpy(sentence, "");
    strcpy(numbers, "");
    
    while (1) {
        printf("\nInsira os números: ");
        scanf(" %s", numbers);
        if (!strcmp(numbers, "1")) {
            break;
        }
        else if (!strcmp(numbers, "0")){
            exit(0);
        }
        
        suggestions(H, sentence, numbers);
    }
    printf("\nMensagem: %s\n\n", sentence);
    
    return up.posnew;
}

