#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <string.h>
#include "edge.h"

// Move to general library eventually
struct EdgeList* createEdgeList();

struct EdgeListItem* createEdgeListItem(struct Edge* e);

struct Edge* removeFirst(struct EdgeList* edge_list);

struct Edge* removeLast(struct EdgeList* edge_list);

void appendEdge(struct EdgeList* edge_list, struct Edge* e);

void prependEdge(struct EdgeList* edge_list, struct Edge* e);

int removeEdge(struct EdgeList* edge_list, struct Edge* e);

#endif