#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "lockedobject.h"
#include "node.h"
#endif

struct NodeListItem* createNodeListItem(struct Node* e);

struct NodeList* createNodeList();

struct Node* head_NL(struct NodeList* node_list);

struct Node* tail_NL(struct NodeList* node_list);

struct Node* removeFirst_NL(struct NodeList* node_list);

struct Node* removeLast_NL(struct NodeList* node_list);

void prependNode(struct NodeList* node_list, struct Node* e);

bool empty_NL(struct NodeList* node_list);

int length_NL(struct NodeList* node_list);

void appendNode(struct NodeList* node_list, struct Node* n);

int removeNode(struct NodeList* node_list, struct Node* e);

bool includesNode(struct NodeList* nl, struct Node* n);

struct NodeList* neighbors(struct Node* node);
