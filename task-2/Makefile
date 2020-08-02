CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11 -pedantic

all: write_matrix read_matrix

write_matrix: write_matrix.o
	$(CC) $(CFLAGS) $< -o $@

read_matrix: read_matrix.o
	$(CC) $(CFLAGS) $< -o $@ 

write_matrix.o: write_matrix.c
	$(CC) $(CFLAGS) -c $< -o $@ 

read_matrix.o: read_matrix.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *_matrix
