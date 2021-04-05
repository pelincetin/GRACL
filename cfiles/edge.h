#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdio.h>
#include "commonFunctions.h"

void updateEdge(double new_weight, struct Edge* edge);

double weight(struct Edge* edge);

/* New start and end accessors */
struct Node* start(struct Edge* edge);

struct Node* end(struct Edge* edge);

#endif
