CC = gcc
CFLAGS = -g -Wall -std=c99 -pedantic

print_pids_child3: print_pids_child3.c
	$(CC) $(CFLAGS) $< -o $@

run: print_pids_child3
	./print_pids_child3

clean:
	rm -rf print_pids_child3
