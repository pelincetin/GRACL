CC = gcc
CFLAGS = -g -Wall

.PHONY: node
node: node.h
	$(CC) $(CFLAGS) -pthread -o node node.h

.PHONY: node-test
node-test: node-test.c
	$(CC) $(CFLAGS) -pthread -o node-test node-test.c

.PHONY: edge
edge: edge.h
	$(CC) $(CFLAGS) -pthread -o edge edge.h

.PHONY: edge-test
edge-test: edge-test.c
	$(CC) $(CFLAGS) -pthread -o edge-test edge-test.c

.PHONY: edgelist
edgelist: edgelist.h
	$(CC) $(CFLAGS) -pthread -o edgelist edgelist.h

.PHONY: edgelist-test
edgelist-test: edgelist-test.c
	$(CC) $(CFLAGS) -pthread -o edgelist-test edgelist-test.c

.PHONY: clean
clean:
	rm -f *.o node edge
