#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "nodelist.h"
#include "edgelist.h"
#include "edge.h"
#endif

/* 
 * The key of the graph hashtbl is going to be a node
 * The value will be a nodelist of nodes having an edge to the key
 */
struct Graph* createGraph(int size);

int hashCode(struct Graph* g, struct Node* node);

void incrementId(struct Graph* g);

void incrementGraphId();

/* Returns a nodelist of nodes in the graph
 * sorted by order of creation
 */
struct NodeList* nodes(struct Graph* g);

struct Node* createNode(struct Graph* g, char* data);

int removeEdgeGraph(struct Graph* g, struct Edge* e);

/* 
 * Go through nodelist and delete node from:
 * overall graph's nodelist
 * and remove all edges from the value list
 * for all edges of node to delete, delete these from other value lists
 */
int removeNodeGraph(struct Graph* g, struct Node* n);

struct Edge* addEdge(struct Graph* g, struct Node* start_node, struct Node* end_node, double edge_weight);