#include <stdlib.h>
#include <stdio.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

void updateEdge(double new_weight, struct Edge* edge) {
    edge->weight = new_weight;
    return;
}

double weight(struct Edge* edge) {
    return edge->weight;
}


int main(){
    return 0;
}
