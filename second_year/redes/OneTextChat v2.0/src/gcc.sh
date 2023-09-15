#!/bin/sh
printf "\nCompiling Client...\n\n"
gcc -c client.c
gcc -c client_functions.c
gcc -c client_functions.h
gcc -c list.c 
gcc -c list.h
gcc -o client client.o  client_functions.o list.o -lm -ggdb3 
printf "\nCompiling Server...\n\n"
gcc -c server.c
gcc -c server_functions.c
gcc -c server_functions.h
gcc -c list.c
gcc -c list.h
gcc -c fatal.h
gcc -c string_functions.c
gcc -c string_functions.h
gcc -o server server.o  server_functions.o list.o string_functions.o -lm
rm server.o
rm server_functions.o
rm server_functions.h.gch
rm list.h.gch
rm list.o
rm fatal.h.gch
rm client.o
rm client_functions.o
rm client_functions.h.gch
rm string_functions.o
rm string_functions.h.gch