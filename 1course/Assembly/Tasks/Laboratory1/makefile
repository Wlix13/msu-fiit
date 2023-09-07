all: run

transform.o: transform.asm
	nasm -W+all -g -f elf32 -D UNIX transform.asm -o transform.o
main: main.c transform.h transform.o
	gcc -Wall -m32 main.c transform.o -o main
run: main
	./main
<<<<<<< Updated upstream
	
=======
>>>>>>> Stashed changes
