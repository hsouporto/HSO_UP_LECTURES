CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_DEFAULT_SOURCE

parcc: parcc.c
	$(CC) $(CFLAGS) parcc.c -o parcc

clean:
	rm -f parcc
	rm -f examples/*/*.o examples/hello/hello examples/calc/calc examples/stats/stats examples/broken/broken

.PHONY: clean
