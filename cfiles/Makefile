CC = gcc
CFLAGS = -g -Wall

.PHONY: node
node: node.c 
	$(CC) $(CFLAGS) -pthread -o node lockedobject.h node.c

.PHONY : clean
clean:
	rm -f node
