CC = gcc
CFLAGS = -g -Wall -std=c99 -pedantic

lex_min: main.o ring.o
	$(CC) $(CFLAGS) $^ -o $@

ring.o: ring.c ring.h
	$(CC) $(CFLAGS) $< -c -o $@

main.o: main.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf *.o lex_min
