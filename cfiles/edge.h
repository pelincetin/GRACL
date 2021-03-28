#include <stdlib.h>
#include <stdio.h>
#include "node.h"

// this function is not intended for the user, right?
void printEdge(struct Edge* edge) {
    printf("Start node: %s", edge->start->data);
    printf("End node: %s", edge->end->data);
    printf("Weight: %f", edge->weight);
}

// SHOULD GO IN GRAPH EVENTUALLY!
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

bool edgeEquals(struct Edge* e1, struct Edge* e2) {
    return (((e1->weight == e2->weight) && nodeEquals(e1->start, e2->start)) && nodeEquals(e1->end, e2->end));
}

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