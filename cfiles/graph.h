#ifndef GRAPH_H
#define GRAPH_H

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "commonFunctions.h"
#include "node.h"

/* The key is going to be node
 * the value would a nodelist whose edges point to the key */
struct Graph* createGraph();

int hashCode(struct Node* node);

struct NodeList* nodes(struct Graph* g);

struct Node* createNode(struct Graph* g, char* data);

int removeNodeGraph(struct Graph* g, struct Node* e);

int removeEdgeGraph(struct Graph* g, struct Edge* e);

struct Edge* addEdge(struct Node* start_node, struct Node* end_node, double edge_weight);

#endif