#include <stdlib.h>
#include <stdio.h>
#include "lockedobject.h"


void updateEdge(double new_weight, struct LockedEdge* edge) {
    edge->weight = new_weight;
    return;
}

double weight(struct LockedEdge* edge) {
    return edge->weight;
}