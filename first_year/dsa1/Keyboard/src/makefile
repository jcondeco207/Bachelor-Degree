all: keyboard.c
	gcc -c keyboard.c
	gcc -c functions.c
	gcc -c hashsep.c
	gcc -o keyboard keyboard.o functions.o hashsep.o
	rm keyboard.o functions.o hashsep.o