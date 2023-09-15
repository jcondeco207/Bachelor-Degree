#!/bin/sh
gcc -c main.c
gcc -c functions.c
gcc -c fatal.h
gcc -c functions.h
gcc -c queue.h
gcc -c queue.c
gcc -c list.c
gcc -c list.h
gcc -o main main.o functions.o queue.o list.o
