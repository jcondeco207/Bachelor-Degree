//
//  keyboard.c
//
//
// _              _                         _
//| | _____ _   _| |__   ___   __ _ _ __ __| |
//| |/ / _ \ | | | '_ \ / _ \ / _` | '__/ _` |
//|   <  __/ |_| | |_) | (_) | (_| | | | (_| |
//|_|\_\___|\__, |_.__/ \___/ \__,_|_|  \__,_|
//          |___/
//
//  Created by João Condeço and Sara Amaral on 30/05/2021.
//

#include <stdio.h>
#include "functions.h"
#include <time.h>

#define BILLION 1000000000L;

//Mostra a palavra "keyboard"
void ShowTitle(void){
    printf("\n\n");
    printf(" _              _                         _\n| | _____ _   _| |__   ___   __ _ _ __ __| |\n| |/ / _ \\ | | | '_ \\ / _ \\ / _` | '__/ _` |\n|   <  __/ |_| | |_) | (_) | (_| | | | (_| |\n|_|\\_\\___|\\__, |_.__/ \\___/ \\__,_|_|  \\__,_|\n          |___/                             ");
    printf("\n\n");
}

//Mostra o menu com as opções possiveis
void ShowMenu(void){
    printf("\n ");
    PrintChars(51, '-');
    printf("\n|    Este programa contempla as seguintes opções:   |\n|                                                   |\n|\t0 -> Terminar o programa                    |\n|\t1 -> Carregar o dicionário                  |\n|\t2 -> Informação acerca dos digitos          |\n|\t3 -> Modo Escrita                           |\n|\t4 -> Esta mensagem                          |\n|                                                   |\n");
    printf(" ");
    PrintChars(51, '-');
    printf("\n\n");
}

//Mostra o teclado
void ShowInstructions(void){
    printf("\n ");
    PrintChars(45, '-');
    printf("\n|\t1: Termina a inserção da mensagem     |\n|\t2: a b c á à â ã ç                    |\n|\t3: d e f é ê                          |\n|\t4: g h i í                            |\n|\t5: j k l                              |\n|\t6: m n o ó ô õ                        |\n|\t7: p q r s                            |\n|\t8: t u v ú                            |\n|\t9: w x y z                            |\n");
    printf(" ");
    PrintChars(45, '-');
    printf("\n\n");
}


int main(int argc, const char * argv[]) {
    int option;
    int loaded = 0;
    int *ploaded = &loaded;
    int need = 0;
    int has_frequencies = 0;
    int *phf = &has_frequencies;
    

    ShowTitle();
    ShowMenu();
    
    HashTable H = InitializeTable(tablesz);
    if (argc > 1) {
        H = AddDict(H, argv, argc, 0, phf, ploaded);
    }
    else{
        printf("\n=> Atenção! Como não carregou um dicionário será necessário carregar um para aceder à secção 3! <=\n\n");
    }
    
    while(1){
        printf("Insira a opção que deseja: ");
        scanf(" %d", &option);
        if(option == 0){
            break;
        }
        else if(option == 1){
            
            struct timespec start, stop;
            double accum;
            clock_gettime( CLOCK_REALTIME, &start );

            H = AddDict(H, argv, argc, 1, phf, ploaded);
            
            clock_gettime( CLOCK_REALTIME, &stop );
            accum = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / (double) BILLION;
            printf( "Tempo de carregamento: %f\n\n", accum );
            loaded = 1;
            
            
        }
        else if(option == 2){
            ShowInstructions();
        }
        else if(option == 3){
            if(loaded == 1){
                need = Receiver(H);
            }
            else{
                printf("\nTem de carregar um dicionário para poder executar\n\n");
            }
        }
        else if(option == 4){
            ShowMenu();
        }
        else{
            printf("Opção inválida, por favor tente novamente.\nEm caso de dúvida consulte o tutorial (insira 4)\n\n");
        }
    }
    
    if (need > 0) {
        upload(has_frequencies);
    }
    
    DestroyTable(H);
    return 0;
}
