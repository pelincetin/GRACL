#ifndef NODE_H
#define NODE_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "commonFunctions.h"

const char* data(struct Node* node);

/* Neturn the node neighbors of a node
 * Meaning every node it contains an edge to */ 
struct NodeList* neighbors(struct Node* node);

struct EdgeList* edges(struct Node* node);

/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct Node* node);

struct Node* updateData(char* new_data, struct Node* node);

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(bool tf, struct Node* node);

#endif