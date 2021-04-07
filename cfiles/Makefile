CC = gcc
CFLAGS = -g -Wall

.PHONY: all
all: node edge edgelist nodelist graph

.PHONY: node
node: node.c
	$(CC) $(CFLAGS) -pthread -o node node.c

.PHONY: edge
edge: edge.c
	$(CC) $(CFLAGS) -pthread -o edge edge.c

.PHONY: edgelist
edgelist: edgelist.c
	$(CC) $(CFLAGS) -pthread -o edgelist edgelist.c

.PHONY: nodelist
nodelist: nodelist.c
	$(CC) $(CFLAGS) -pthread -o nodelist nodelist.c

.PHONY: graph
graph: graph.c
	$(CC) $(CFLAGS) -pthread -o graph graph.c

.PHONY: clean
clean:
	rm -f *.o node edge edgelist nodelist graph