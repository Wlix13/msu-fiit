CC=gcc
CFLAGS=-Wall -Werror 

all: server client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

client: client.c
	$(CC) $(CFLAGS) client.c -o client

run_server:
	./server 50000

run_client:
	./client 127.0.0.1 50000

clean:
	rm -f server client