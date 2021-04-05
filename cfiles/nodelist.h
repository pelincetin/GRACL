#ifndef NODE_LIST_H
#define NODE_LIST_H

#include <stdlib.h>
#include <string.h>
#include "commonFunctions.h"

/* Move to general library eventually */
struct NodeList* createNodeList();

struct Node* removeFirst(struct NodeList* node_list);

struct Node* removeLast(struct NodeList* node_list);

int removeNode(struct NodeList* node_list, struct Node* e); 

void prependNode(struct NodeList* node_list, struct Node* e);

void appendNode(struct NodeList* node_list, struct Node* n);

#endif
