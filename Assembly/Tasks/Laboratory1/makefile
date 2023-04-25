all: run

lib.o: lib.asm
	nasm -W+all -g -f elf32 -D UNIX lib.asm -o lib.o
main: main.c lib.h lib.o
	gcc -Wall -m32 main.c lib.o -o main
run: main
	/data/build/main
	