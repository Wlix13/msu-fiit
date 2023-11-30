CC=gcc
CFLAGS=-Wall -Wextra
BUILD_DIR = ./build
INCLUDE_CMD = `pkg-config --cflags --libs libmongoc-1.0`
UNAME := $(shell uname)

all: server client

driver:
ifeq ($(UNAME), Darwin)
	brew install mongo-c-driver
else
	sudo apt install libmongoc-dev
endif
	mkdir -p $(BUILD_DIR)

mongo: mongo.c
	$(CC) $(CFLAGS) -c mongo.c -o $(BUILD_DIR)/mongo.o $(INCLUDE_CMD)
server: server.c mongo
	$(CC) $(CFLAGS) server.c mongo.o -o $(BUILD_DIR)/server $(INCLUDE_CMD)

client: client.c
	$(CC) $(CFLAGS) client.c -o $(BUILD_DIR)/client

run_server:
	./server 50000

run_client:
	./client 127.0.0.1 50000

clean:
	rm -f server client mongo.o