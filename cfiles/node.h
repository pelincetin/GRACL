#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BUILDSTDLIB
#include "lockedobject.h"
#include "edge.h"
#endif

const char* data(struct Node* node);

/* Return the edgelist of surrounding edges */
struct EdgeList* edges(struct Node* node);

/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct Node* node);

struct Node* updateData(struct Node* node, char* new_data);

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(struct Node* node, bool tf);

int cost(struct Node* node);

int incrementCost(struct Node* node);

int decrementCost(struct Node* node);

int updateCost(struct Node* node, int new_cost);

struct Node* prec(struct Node* node);

struct Node* setPrec(struct Node* node, struct Node* precursor);

bool nodeEquals(struct Node* node1, struct Node* node2);

/* TODO: NEEDS TESTING */
struct Edge* getEdge(struct Node* node1, struct Node* node2);
