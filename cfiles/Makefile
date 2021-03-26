CC = gcc
CFLAGS = -g -Wall

.PHONY: node
node: node.c
	$(CC) $(CFLAGS) -pthread -o node node.c

.PHONY: clean
clean:
	rm -f *.o
