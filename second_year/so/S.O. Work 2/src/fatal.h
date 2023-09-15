//------------------------------------------------------------------------------------//
// Trabalho de S.O.(Simulador de Sistema Operativo)

// Engenharia Informática, Universidade de Évora
// Joana Carrasqueira (nº 48566), João Condeço (nº 48976) e João Oliveira (nº 48979)
// Abril de 2022
//-----------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )
