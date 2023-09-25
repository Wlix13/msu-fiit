lib.o: list.h list.c
	gcc -Wall -c list.c -o lib.o
main: lib.o main.c
	gcc -Wall main.c lib.o -o main
run: main
	valgrind ./main
clean:
	rm lib.o main
