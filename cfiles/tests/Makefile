CC = gcc
CFLAGS = -g -Wall

.PHONY: all
all: node-test edge-test nodelist-test edgelist-test graph-test concurrency-test inttable-test doubletable-test dijkstra-test normaldfs-test

.PHONY: node-test
node-test: node-test.c
	$(CC) $(CFLAGS) -pthread -o node-test node-test.c

.PHONY: edge-test
edge-test: edge-test.c
	$(CC) $(CFLAGS) -pthread -o edge-test edge-test.c

.PHONY: edgelist-test
edgelist-test: edgelist-test.c
	$(CC) $(CFLAGS) -pthread -o edgelist-test edgelist-test.c

.PHONY: nodelist-test
nodelist-test: nodelist-test.c
	$(CC) $(CFLAGS) -pthread -o nodelist-test nodelist-test.c

.PHONY: graph-test
graph-test: graph-test.c
	$(CC) $(CFLAGS) -pthread -o graph-test graph-test.c

.PHONY: concurrency-test
concurrency-test: concurrency-test.c
	$(CC) $(CFLAGS) -pthread -o concurrency-test concurrency-test.c

.PHONY: inttable-test
inttable-test: inttable-test.c
	$(CC) $(CFLAGS) -pthread -o inttable-test inttable-test.c

.PHONY: doubletable-test
doubletable-test: doubletable-test.c
	$(CC) $(CFLAGS) -pthread -o doubletable-test doubletable-test.c

.PHONY: dijkstra-test
dijkstra-test: dijkstra-test.c
	$(CC) $(CFLAGS) -pthread -o dijkstra-test dijkstra-test.c

.PHONY: normaldfs-test
normaldfs-test: normalDFS-conc.c
	$(CC) $(CFLAGS) -pthread -o normaldfs-test normalDFS-conc.c

.PHONY: clean
clean:
	rm -f *.o node-test edge-test edgelist-test nodelist-test graph-test inttable-test doubletable-test dijkstra-test concurrency-test normaldfs-test
