CC = gcc
CFLAGS = -g -Wall

.PHONY: node
node: node.c
	$(CC) $(CFLAGS) -pthread -o node node.c

.PHONY: edge
edge: edge.c
	$(CC) $(CFLAGS) -pthread -o edge edge.c

.PHONY: clean
clean:
	rm -f *.o node edge
