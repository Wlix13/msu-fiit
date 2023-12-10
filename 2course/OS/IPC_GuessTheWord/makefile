CC = clang
CFLAGS = -Wall -Wextra
BUILDDIR = ./build
INCLUDEFLAGS = $(shell pkg-config --cflags --libs libmongoc-1.0)
UNAME := $(shell uname)

.PHONY: all clean driver

all: $(BUILDDIR)/server $(BUILDDIR)/client

$(BUILDDIR)/mongo.o: mongo.c
	$(CC) $(CFLAGS) -c mongo.c -o $@ $(INCLUDEFLAGS)

$(BUILDDIR)/server: server.c -lpthread $(BUILDDIR)/mongo.o
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDEFLAGS)

$(BUILDDIR)/client: client.c
	$(CC) $(CFLAGS) $< -o $@

driver:
ifeq ($(UNAME), Darwin)
	brew install mongo-c-driver
else
	sudo apt install libmongoc-dev
endif
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)/*.o $(BUILDDIR)/server $(BUILDDIR)/client