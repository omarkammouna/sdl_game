# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Libraries
LIBS = -lSDL -lSDL_ttf -lSDL_image

# Source files
SRCS = main.c function.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = game

# Main target
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(EXEC)

