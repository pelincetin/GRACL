CC = gcc
CFLAGS = -g -Wall

.PHONY: all
all: node edge edgelist nodelist 

.PHONY: node
node: node.h
	$(CC) $(CFLAGS) -pthread -o node node.h

.PHONY: edge
edge: edge.h
	$(CC) $(CFLAGS) -pthread -o edge edge.h

.PHONY: edgelist
edgelist: edgelist.h
	$(CC) $(CFLAGS) -pthread -o edgelist edgelist.h

.PHONY: nodelist
nodelist: nodelist.h
	$(CC) $(CFLAGS) -pthread -o nodelist nodelist.h

.PHONY: clean
clean:
	rm -f *.o node edge edgelist nodelist
