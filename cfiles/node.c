#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BUILDSTDLIB
#include "lockedobject.h"
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

struct Node* updateData(struct Node* node, char* new_data)
{
    node->data = new_data;
    return node;
}

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(struct Node* node, bool tf)
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
    return node;
}

bool nodeEquals(struct Node* node1, struct Node* node2)
{
    if (node1->id == node2->id) {
        return true;
    }
    return false;
}