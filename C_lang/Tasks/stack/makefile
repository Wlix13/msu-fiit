lib.o: stack.h stack_lib.c
	gcc -Wall -c stack_lib.c -o lib.o
main: lib.o postfix_calculator.c
	gcc -Wall postfix_translator.c lib.o -o transl
	gcc -Wall postfix_calculator.c lib.o -o  calc
run: main
	 ./transl | ./calc