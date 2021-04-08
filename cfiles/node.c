#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

const char* data(struct Node* node)
{
    return node->data;
}

/* Return the edgelist of surrounding edges */
struct EdgeList* edges(struct Node* node)
{
    return node->edges; 
}

/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct Node* node)
{
    return node->visited;
}

struct Node* updateData(char* new_data, struct Node* node)
{
    node->data = new_data;
    return node;
}

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(bool tf, struct Node* node)
{
    node->visited = tf;
    return node;
}

int cost(struct Node* node)
{
    return node->cost;
}

int incrementCost(struct Node* node)
{
    node->cost = node->cost + 1;
    return node->cost;
}

int decrementCost(struct Node* node)
{
    node->cost = node->cost - 1;
    return node->cost;
}

int updateCost(struct Node* node, int new_cost)
{
    node->cost = new_cost;
    return node->cost;
}

struct Node* prec(struct Node* node)
{
    return node->precursor;
}

struct Node* set_prec(struct Node* node, struct Node* precursor)
{
    node->precursor = precursor;
    return node->precursor;
}