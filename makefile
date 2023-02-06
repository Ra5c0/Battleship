projet: projet.o
	gcc -o projet projet.o

projet.o: projet.c
	gcc -o projet.o -c projet.c -W -Wall -ansi -pedantic -std=c99
