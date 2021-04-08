#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "lockedobject.h"

bool nodeEquals(struct Node* node1, struct Node* node2);

/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct Node* node);

bool edgeEquals(struct Edge* e1, struct Edge* e2);

bool empty_NL(struct NodeList* node_list);

bool empty_EL(struct EdgeList* edge_list);

// Return the data of the node
const char* data(struct Node* node);

int hashCode(struct Graph* g, struct Node* node);

int length_EL(struct EdgeList* edge_list);

int length_NL(struct NodeList* node_list);

int removeNode(struct NodeList* node_list, struct Node* e); 

int removeEdge(struct EdgeList* edge_list, struct Edge* e);

int removeNodeGraph(struct Graph* g, struct Node* e);

int removeEdgeGraph(struct Graph* g, struct Edge* e);

double weight(struct Edge* edge);

/* New start and end accessors */
struct Node* start(struct Edge* edge);

struct Node* end(struct Edge* edge);

struct Node* createNode(struct Graph* g, char* data);

struct Node* updateData(char* new_data, struct Node* node);

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(bool tf, struct Node* node);

struct Node* removeFirst_NL(struct NodeList* node_list);

struct Node* removeLast_NL(struct NodeList* node_list);

/* Move to general library eventually */
struct NodeList* createNodeList();

/* Return the node neighbors of a node
 * Meaning every node it contains an edge to */ 
struct NodeList* neighbors(struct Node* node);

struct NodeList* nodes(struct Graph* g);

struct NodeListItem* createNodeListItem(struct Node* e);

struct Edge* addEdge(struct Graph* g, struct Node* start_node, struct Node* end_node, double edge_weight);

struct Edge* removeFirst_EL(struct EdgeList* edge_list);

struct Edge* removeLast_EL(struct EdgeList* edge_list);

struct EdgeListItem* createEdgeListItem(struct Edge* e);

// Move to general library eventually
struct EdgeList* createEdgeList();

struct EdgeList* edges(struct Node* node);

/* The key is going to be node
 * the value would a nodelist whose edges point to the key */
struct Graph* createGraph();

void prependNode(struct NodeList* node_list, struct Node* n);

void appendNode(struct NodeList* node_list, struct Node* n);

void appendEdge(struct EdgeList* edge_list, struct Edge* e);

void prependEdge(struct EdgeList* edge_list, struct Edge* e);

void updateEdge(double new_weight, struct Edge* edge);