#include <stdlib.h>
#include <stdio.h>
#ifndef BUILDSTDLIB
#include "node.c"
#endif 

void updateEdge(double new_weight, struct Edge* edge) {
    edge->weight = new_weight;
    return;
}

double weight(struct Edge* edge) {
    return edge->weight;
}

bool edgeEquals(struct Edge* e1, struct Edge* e2) {
    return (((e1->weight == e2->weight) && nodeEquals(e1->start, e2->start)) && nodeEquals(e1->end, e2->end));
}

/* New start and end accessors */
struct Node* start(struct Edge* edge) {
    return edge->start;
}

struct Node* end(struct Edge* edge) {
    return edge->end;
}