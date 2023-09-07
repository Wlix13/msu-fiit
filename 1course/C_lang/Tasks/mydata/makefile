lib.o: mydata.h mydata.c
	gcc -Wall -c mydata.c -o lib.o
main: lib.o main.c
	gcc -Wall main.c lib.o -o main
run: main
	 ./main