/*__  __ _
//|  \/  (_)_ __   ___  _____      _____  ___ _ __   ___ _ __
//| |\/| | | '_ \ / _ \/ __\ \ /\ / / _ \/ _ \ '_ \ / _ \ '__|
//| |  | | | | | |  __/\__ \\ V  V /  __/  __/ |_) |  __/ |
//|_|  |_|_|_| |_|\___||___/ \_/\_/ \___|\___| .__/ \___|_|
//                                          |_|
//
//Minesweeper
//
//  Created by João Condeço and Pedro Leitão on 20/12/2020.
*/

#include <stdio.h>
#include "mine_functions.h"

// Recolhe e retorna a opção inicial de jogo
int wish(){
    int option;
    printf("Deseja jogar novamente?\n1 - Sim\nQualquer outro número - Não\n\nA sua opção: ");
    scanf("%d", &option);
    
    return option;
}


int main(int argc, const char * argv[]) {
    
    int option, aux1 = 1;
    
    //Mensagem do inicio do jogo
    printf(" __  __ _\n|  \\/  (_)_ __   ___  _____      _____  ___ _ __   ___ _ __\n| |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n| |  | | | | | |  __/\\__ \\ V  V /  __/  __/ |_) |  __/  |\n|_|  |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|\n                                           |_|\n\n");
    
    
    while(aux1 == 1){
        
        printf("Menu|\n\t|-> 0 -> Sair\n\t|\n\t|-> 1 -> Tutorial\n\t|\n\t|-> 2 -> Gerar tabuleiro\n\t|\n\t|-> 3 -> Ler tabuleiro\n\n\t A sua opção: ");
        scanf("%d", &option);
        
        
        if ((option >=0) && (option<=3)) {
            
            if (option == 0) {
                aux1 +=1;
            }
            
            else if (option == 1){
                printf("\nInstruções:\n\n\tBem vindo ao Minesweeper\n\n\t1º -> terá de escolher o modo de jogo: Gerar tabuleiro ou Ler tabuleiro.\n\n\t2º -> Caso tenha escolhido a opção Gerar Tabuleiro terá de inserir as dimensões do mesmo e o número de minas no formato indicado\n\tPor exemplo: 10 10 15.\n\tCaso deseje inserir um tabuleiro seu só tem de se preocupar em inserir a localização de um ficheiro com o formato correto.\n\n\t3º -> Deve proceder ao jogo. No jogo as jogadas são constituidas pelas coordenadas + a ação desejada.\n\tPor exemplo a jogada 10 A u irá efetuar o uncover na linha 10, coluna 1\n\n\tO jogo termina quando todas as casas que não sejam minas estejam destapadas, todas as minas tenham uma flag e nenhuma esteja num sitio que não seja mina.\n\tBom jogo e divirta-se ;)\n\n");
            }
            
            else if(option == 2){
                data();
                aux1 = wish();
            }
            
            else{
                struct board d;
                d = receiver();
                game(d, d.nlines, d.ncols, 0);
                aux1 = wish();
            }
        }
        
        else{
            printf("\nValor introduzido incorreto, tente novamente.\n\n");
        }
        
    }
    
    printf("\n\nGoodbye Player\n\n");
    
    return 0;
}
