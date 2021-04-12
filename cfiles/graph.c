#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "nodelist.c"
#include "edgelist.c"
#include "edge.c"
#endif

/* 
 * The key of the graph hashtbl is going to be a node
 * The value will be a nodelist of nodes having an edge to the key
 */
struct Graph* createGraph(int size) {
    struct DataItem* d = malloc(sizeof(struct DataItem) * size);
    for (int i = 0; i < size; i++) {
        d[i].key = NULL;
        d[i].value = NULL;
    }
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->hashArray = d;
    graph->size = size;
    graph->nodes = createNodeList();
    return graph;
}

int hashCode(struct Graph* g, struct Node* node) {
    int id_node = node->id;
    return id_node % g->size;
}

void incrementId(){
    id_num++;
}

/* Returns a nodelist of nodes in the graph
 * sorted by order of creation
 */
struct NodeList* nodes(struct Graph* g){
    return g->nodes;
}

struct Node* createNode(struct Graph* g, char* data) {
    struct Node* node = malloc(sizeof(struct Node));
    struct EdgeList* el = createEdgeList();
    node->data = data;
    node->visited = false;
    node->cost = 0;
    node->precursor = NULL;
    node->id = id_num;
    node->edges = createEdgeList();
    incrementId();
    g->hashArray[hashCode(g, node)].key = node;
    g->hashArray[hashCode(g, node)].value = el;
    if (pthread_mutex_init(&node->lock, NULL) !=0) {
        fprintf(stderr, "createNode: Failure to initialize mutex\n");
        exit(1); 
    } 
    appendNode(g->nodes, node);
    return node; 
}

int removeEdgeGraph(struct Graph* g, struct Edge* e) {
    // remove edge from value list of end_node
    struct EdgeList* values;
    struct Node* end_node = end(e);
    values = g->hashArray[hashCode(g, end_node)].value;
    removeEdge(values, e);

    // remove edge from node internal edgelist of start
    struct EdgeList* edge_list;
    struct Node* start_node = start(e);
    edge_list = start_node->edges;
    removeEdge(edge_list, e);
    return 0;
}


/* 
 * Go through nodelist and delete node from:
 * overall graph's nodelist
 * and remove all edges from the value list
 * for all edges of node to delete, delete these from other value lists
 */
int removeNodeGraph(struct Graph* g, struct Node* n) {
    struct NodeList* all_nodes;
    struct EdgeList* values;
    struct EdgeListItem* list_item = NULL; 

    all_nodes = nodes(g);
    removeNode(all_nodes, n);

    // get values
    values = g->hashArray[hashCode(g, n)].value;
    if (values) {
        list_item = values->head;
    }
    
    // iterate through values and removeEdgeGraph for each
    while (list_item) {
        removeEdgeGraph(g, list_item->edge);
        list_item = list_item->next;
    }
    // null out the values
    g->hashArray[hashCode(g, n)].value = NULL;

    // Now, take care of the key 
    // iterate through edgelist and remove
    // edge from every valuelist where it occurs
    struct EdgeList* node_edges; 
    node_edges = n->edges;

    if (node_edges) {
        list_item = node_edges->head;
    }
    
    while (list_item) {
        struct Edge* e = list_item->edge;
        struct Node* end_n = end(e);
        values = g->hashArray[hashCode(g, end_n)].value;
        if (values) {
            removeEdge(values, e);
        }
        free(e);
        list_item = list_item->next;
    }

    // null out key
    g->hashArray[hashCode(g, n)].key = NULL;

    // free the node memory? 
    free(n);

    return 0;
}

struct Edge* addEdge(struct Graph* g, struct Node* start_node, struct Node* end_node, double edge_weight) {
    struct Edge* edge = malloc(sizeof(struct Edge));
    edge->start = start_node;
    edge->end = end_node;
    edge->weight = edge_weight;
    if (pthread_mutex_init(&edge->lock, NULL) !=0) {
        fprintf(stderr, "addEdge: Failure to initialize mutex\n");
        exit(1); 
    }
    else {
        appendEdge(start_node->edges, edge);
        struct EdgeList* values;
        values = g->hashArray[hashCode(g, end_node)].value;
        appendEdge(values, edge);
        return edge;
    }
}