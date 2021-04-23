#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "lockedobject.h"
#endif

struct EdgeList* createEdgeList();

struct EdgeListItem* createEdgeListItem(struct Edge* e);

struct Edge* head_EL(struct EdgeList* edge_list);

struct Edge* tail_EL(struct EdgeList* edge_list);

struct Edge* removeFirst_EL(struct EdgeList* edge_list);

struct Edge* removeLast_EL(struct EdgeList* edge_list);

void prependEdge(struct EdgeList* edge_list, struct Edge* e);

bool empty_EL(struct EdgeList* edge_list);

int length_EL(struct EdgeList* edge_list);

int removeEdge(struct EdgeList* edge_list, struct Edge* e);

void appendEdge(struct EdgeList* edge_list, struct Edge* e);
