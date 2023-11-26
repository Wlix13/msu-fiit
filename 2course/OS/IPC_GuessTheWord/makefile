CC=gcc
CFLAGS=-Wall 
INCLUDEFLAGS=-lmongoc-1.0 -lbson-1.0

all: server client

mongo: mongo.c
	$(CC) $(CFLAGS) -c mongo.c -o mongo.o $(INCLUDEFLAGS)

server: server.c
	$(CC) $(CFLAGS) server.c mongo.o -o server

client: client.c
	$(CC) $(CFLAGS) client.c -o client

run_server:
	./server 50000

run_client:
	./client 127.0.0.1 50000

clean:
	rm -f server client 