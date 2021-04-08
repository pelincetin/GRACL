#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif
/* The key is going to be a node
 * The value will be a nodelist whose edges point to the key
 */
struct Graph* createGraph(){
    struct DataItem* d = malloc(sizeof(struct DataItem) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        d[i].key = NULL;
        d[i].value = NULL;
    }
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->hashArray = d;
    return graph;
}

int hashCode(struct Node* node) {
    int id_node = node->id;
    return id_node % SIZE;
}

void incrementId(){
    id_num++;
}

void printNodeList(struct NodeList* node_list) {
    struct NodeListItem *current;
    current = node_list->head;
    if(current == NULL)
        fprintf(stderr, "yo this is null\n");
    while (current != NULL) {
        printf("%s\n", current->node->data); 
        current = current->next;
    }
}

/* Returns a nodelist of nodes in the graph
 * sorted by hashed id */
struct NodeList* nodes(struct Graph* g){
    struct NodeList* nodes = malloc(sizeof(struct NodeList));
    for (int i = 0; i < SIZE; i++){
        if (g->hashArray[i].key != NULL){
            appendNode(nodes, g->hashArray[i].key);
        }
    }
    return nodes;
}

struct Node* createNode(struct Graph* g, char* data) {
    struct Node* node = malloc(sizeof(struct Node));
    struct EdgeList* edge_list = malloc(sizeof(struct EdgeList));
    struct NodeList* nl = malloc(sizeof(struct NodeList));
    node->data = data;
    node->visited = false;
    node->id = id_num;
    node->edges = edge_list;
    incrementId();
    g->hashArray[hashCode(node)].key = node;
    g->hashArray[hashCode(node)].value = nl;
    if (pthread_mutex_init(&node->lock, NULL) !=0) {
        fprintf(stderr, "createNode: Failure to initialize mutex\n");
        exit(1); 
    } else {
        //TODO: rn there's no implementation of collision/double size

        // iterate through the list of edges and add
        // a node to the nl in value for each node destination 
        // in the graph structure    
        return node;
    }
}

int removeNodeGraph(struct Graph* g, struct Node* n) {
    // go through nodelist and 
    // delete node from all the nodes' values specified in edge list
    // change hashtbl list 
    struct NodeList* all_nodes = malloc(sizeof(struct NodeList));
    struct NodeList* values = malloc(sizeof(struct NodeList));
    struct NodeListItem* temp = malloc(sizeof(struct NodeListItem));

    all_nodes = nodes(g);
    if (all_nodes != NULL){
        temp = all_nodes->head;
    }else{
        return -1;
    }

    while(temp){
        if(g->hashArray[hashCode(temp->node)].value->head){
            values = g->hashArray[hashCode(temp->node)].value;
            int ret = includesNode(values, temp->node);
            if (ret == 1){
                removeNode(values, temp->node);
            }
        }
        temp = temp->next;
    }

    if (g->hashArray[hashCode(n)].key != NULL){
        g->hashArray[hashCode(n)].value = NULL;
        g->hashArray[hashCode(n)].key = NULL;
    }
    return 0;
}

int removeEdgeGraph(struct Graph* g, struct Edge* e) {
    // remove edge from list 
    struct EdgeList* edge_list;
    edge_list = g->hashArray[hashCode(e->start)].key->edges;
    removeEdge(edge_list, e);

    // remove start node from end node's value list
    struct NodeList* values;
    struct Node* end_node = end(e);
    struct Node* start_node = start(e);
    values = g->hashArray[hashCode(end_node)].value;
    removeNode(values, start_node);
    
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
        struct NodeList* values = malloc(sizeof(struct NodeList));
        values = g->hashArray[hashCode(end_node)].value;
        appendNode(values, start_node);
        printNodeList(g->hashArray[hashCode(end_node)].value);
        return edge;
    }
}

/*
int main(){
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1 = malloc(sizeof(struct Node));
    struct Node* n2 = malloc(sizeof(struct Node));
    n1->data = hello;
    n1->visited = false;
    n1->id=id_num;
    id_num++;

    n2->data = goodbye;
    n2->visited = false;
    n2->id=id_num;
    id_num++;
    struct NodeList* nl = createNodeList();
    appendNode(nl, n1);
    appendNode(nl, n2);
    int ret = includesNode(nl, n1);
    printf("%d\n", ret);

    return 0;
}
*/