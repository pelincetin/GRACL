#include <stdlib.h>
#include <stdio.h>
#ifndef BUILDSTDLIB
#endif 

void updateEdge(struct Edge* edge, double new_weight);

double weight(struct Edge* edge);

bool edgeEquals(struct Edge* e1, struct Edge* e2);

/* New start and end accessors */
struct Node* start(struct Edge* edge);

struct Node* end(struct Edge* edge);