#include <stdlib.h>
#include <stdio.h>
#include "commonFunctions.h"
#include "edge.h"

void updateEdge(double new_weight, struct Edge* edge) {
    edge->weight = new_weight;
    return;
}

double weight(struct Edge* edge) {
    return edge->weight;
}

/* New start and end accessors */
struct Node* start(struct Edge* edge) {
    return edge->start;
}

struct Node* end(struct Edge* edge) {
    return edge->end;
}
