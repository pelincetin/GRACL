#include "graph.h"

/* 
 * The key of the graph hashtbl is going to be a node
 * The value will be a nodelist of nodes having an edge to the key
 */
struct Graph* createGraph(int size) {
    if (size <= 0) {
        fprintf(stderr, "Error: Graph must have be at least size 1 or larger\n");
        exit(1);
    }
    struct DataItem* d = malloc(sizeof(struct DataItem) * size);
    for (int i = 0; i < size; i++) {
        d[i].key = NULL;
        d[i].value = NULL;
    }
    struct Graph* graph = calloc(1, sizeof(struct Graph));
    graph->hashArray = d;
    graph->size = size;
    graph->occupied = 0;
    graph->nodes = createNodeList();
    graph->id_num = 0;
    graph->graph_id_local = graph_id;
    incrementGraphId();
    return graph;
}

void incrementId(struct Graph* g){
    g->id_num++;
}

void incrementGraphId() {
    graph_id++;
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
    node->deleted = false; 
    node->visited = false;
    node->cost = -1.0;
    node->precursor = malloc(sizeof(struct Node));
    node->id = g->id_num;
    node->parent_graph_id = g->graph_id_local;
    node->edges = createEdgeList();
    incrementId(g);
    int size_old = g->size;
    int id_node = node->id;
    g->hashArray[id_node % size_old].key = node;
    g->hashArray[id_node % size_old].value = el;
    g->occupied++;
    if (g->occupied == g->size) {
        int size_new = 2*size_old;
        g->size = size_new;
        // save old array
        struct DataItem* arr = g->hashArray;
        // now calloc new double array
        struct DataItem* dnew = malloc(sizeof(struct DataItem) * size_new);
        for (int i = 0; i < size_new; i++) {
            dnew[i].key = NULL;
            dnew[i].value = NULL;
        } 
        for (int i = 0; i < size_old; i++) {
            dnew[i].key = arr[i].key;
            dnew[i].value = arr[i].value;
        } 
        g->hashArray = dnew;    
    }
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
    values = g->hashArray[end_node->id % g->size].value;
    removeEdge(values, e);

    // remove edge from node internal edgelist of start
    struct EdgeList* edge_list;
    struct Node* start_node = start(e);
    edge_list = start_node->edges;
    removeEdge(edge_list, e);
    e->deleted = true;
    return 0;
}


/* 
 * Go through nodelist and delete node from:
 * overall graph's nodelist
 * and remove all edges from the value list
 * for all edges of node to delete, delete these from other value lists
 */
int removeNodeGraph(struct Graph* g, struct Node* n) {
    struct EdgeList* values;
    struct EdgeListItem* list_item = NULL; 

    removeNode(g->nodes, n);

    // get values
    values = g->hashArray[n->id % g->size].value;
    if (values) {
        list_item = values->head;
    }
    
    // iterate through values and removeEdgeGraph for each
    while (list_item) {
        removeEdgeGraph(g, list_item->edge);
        list_item = list_item->next;
    }
    // null out the values
    g->hashArray[n->id % g->size].value = NULL;

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
        values = g->hashArray[end_n->id % g->size].value;
        if (values) {
            removeEdge(values, e);
        }
        list_item = list_item->next;
    }

    // null out key
    g->hashArray[n->id % g->size].key = NULL;
    n->deleted = true;
    return 0;
}

struct Edge* addEdge(struct Graph* g, struct Node* start_node, struct Node* end_node, double edge_weight) {
    if ((start_node->deleted) || (end_node->deleted)) {
        fprintf(stderr, "addEdge: Start or end node deleted\n");
        exit(1);
    }
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
        values = g->hashArray[end_node->id % g->size].value;
        appendEdge(values, edge);
        return edge;
    }
}