lib.o: list.h list.c
	gcc -Wall -c list.c -o lib.o
main: lib.o main.c
	gcc -Wall main.c lib.o -o main
run: main
	 ./main from.txt to.txt