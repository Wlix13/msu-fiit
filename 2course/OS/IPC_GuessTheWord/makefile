CC=gcc
CFLAGS=-Wall 
INCLUDEFLAGS=-lmongoc-1.0 -lbson-1.0

UNAME := $(shell uname)

all: server client

ifeq ($(UNAME), Darwin)
	# macOS specific commands
	mongo: mongo.c
		$(CC) $(CFLAGS) -c mongo.c -o mongo.o $(pkg-config --cflags --libs libmongoc-1.0)m
else
	# Linux specific commands
	mongo: mongo.c
		$(CC) $(CFLAGS) -c mongo.c -o mongo.o $(INCLUDEFLAGS)
endif

server: server.c
	$(CC) $(CFLAGS) server.c -o server

client: client.c
	$(CC) $(CFLAGS) client.c -o client

run_server:
	./server 50000

run_client:
	./client 127.0.0.1 50000

clean:
	rm -f server client mongo.o