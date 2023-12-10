CC = clang
CFLAGS = -Wall -Wextra -g
SRCDIR = .
MODULES = modules

SOURCES = $(wildcard $(SRCDIR)/*.c)
MODULE_SOURCES = $(wildcard $(MODULES)/*.c)

OBJECTS = $(SOURCES:.c=.o)
MODULE_OBJECTS = $(MODULE_SOURCES:.c=.o)

EXECUTABLE = shell

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MODULE_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(MODULE_OBJECTS) $(EXECUTABLE)