# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra -g

# Directories
SRCDIR := .
MODULES := modules

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.c)
MODULE_SOURCES := $(wildcard $(MODULES)/*.c)

# Object files
OBJECTS := $(SOURCES:.c=.o)
MODULE_OBJECTS := $(MODULE_SOURCES:.c=.o)

# Executable
EXECUTABLE := shell

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MODULE_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(MODULE_OBJECTS) $(EXECUTABLE)