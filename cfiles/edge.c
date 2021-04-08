#include <stdlib.h>
#include <stdio.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

void updateEdge(struct Edge* edge, double new_weight) {
    edge->weight = new_weight;
    return;
}

double weight(struct Edge* edge) {
    return edge->weight;
}

/*
int main(){
    return 0;
}
*/