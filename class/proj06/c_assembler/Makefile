# Define compiler
CC = gcc

# Define compile-time flags
CFLAGS = -g -Wall

# Define the target executable
TARGET = program

# Define source files
SOURCES = program.c cleaner.c parser.c symbol.c hashtable_linked.c

# Define object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for cleaning up the project
clean:
	rm -f $(TARGET) $(OBJECTS)

# Dependency rules for object files
program.o: program.c
cleaner.o: cleaner.c
parser.o: parser.c
symbol.o: symbol.c
hashtable_linked.o: hashtable_linked.c
