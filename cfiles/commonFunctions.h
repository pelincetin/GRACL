#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "lockedobject.h"

bool nodeEquals(struct Node* node1, struct Node* node2);

bool edgeEquals(struct Edge* e1, struct Edge* e2);

bool empty_NL(struct NodeList* node_list);

bool empty_EL(struct EdgeList* edge_list);

int length_EL(struct EdgeList* edge_list);

int length_NL(struct NodeList* node_list);

struct NodeListItem* createNodeListItem(struct Node* e);

#endif