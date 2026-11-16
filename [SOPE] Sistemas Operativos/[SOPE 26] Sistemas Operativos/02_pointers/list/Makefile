CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = list.o
EXEC = use_list

all: $(EXEC)

# Compile list.c into list.o
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c -o list.o

# Compile and link use_list.c with list.o
use_list: use_list.c $(OBJ)
	$(CC) $(CFLAGS) use_list.c $(OBJ) -o $(EXEC)

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)