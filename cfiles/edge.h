#include <stdlib.h>
#include <stdio.h>
#include "commonFunctions.h"

// SHOULD GO IN GRAPH EVENTUALLY!
// destination node has to be added to the source node's value in the hashtable
struct Edge* addEdge(struct Node* start_node, struct Node* end_node, double edge_weight) {
    struct Edge* edge = malloc(sizeof(struct Edge));
    edge->start = start_node;
    edge->end = end_node;
    edge->weight = edge_weight;
    if (pthread_mutex_init(&edge->lock, NULL) !=0) {
        fprintf(stderr, "addEdge: Failure to initialize mutex\n");
        exit(1); 
    }
    else {
        return edge;
    }
};

void updateEdge(double new_weight, struct Edge* edge) {
    edge->weight = new_weight;
    return;
}

double weight(struct Edge* edge) {
    return edge->weight;
}

// Added these accessors to node start and end that weren't in LRM

struct Node* start(struct Edge* edge) {
    return edge->start;
}

struct Node* end(struct Edge* edge) {
    return edge->end;
}
