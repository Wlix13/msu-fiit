lib.o: stack.h stack_lib.c
	gcc -Wall -c stack_lib.c -o lib.o
main: lib.o postfix_calculator.c
	gcc -Wall postfix_calculator.c lib.o -o main
run: main
	 ./main