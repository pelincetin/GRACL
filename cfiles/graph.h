#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "commonFunctions.h"

// the key is going to be node
// the value would a nodelist whose edges  point to the key
struct Graph* createGraph(){
    struct DataItem* d = malloc(sizeof(struct DataItem) * SIZE);
    for(int i =0; i<SIZE; i++){
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

struct NodeList* nodes(struct Graph* g){
    struct NodeList* nodes = malloc(sizeof(struct NodeList));
    for(int i=0; i<SIZE; i++){
        if(g->hashArray[i].key != NULL){
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
        return node;
    }
}

/*
int removeNode(struct Graph* g, struct Node* e) {
    struct NodeList* node_list = malloc(sizeof(struct NodeList));
    node_list = 
    struct NodeListItem* head = node_list->head;
    struct NodeListItem* prev = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    }
    while (head) {
        if (nodeEquals(e, head->node)) {
            if (prev) {
                prev->next = head->next;
            } else {
                node_list->head = head->next;
            }
            return 0;
        }
        prev = head;
        head = head->next;
    }
    return -1;
}

int removeEdge(struct Graph* g, struct Edge* e) {
    struct EdgeList* edge_list = malloc(sizeof(struct EdgeList));
    struct EdgeListItem* head = malloc(sizeof(struct EdgeListItem));
    struct EdgeListItem* prev = malloc(sizeof(struct EdgeListItem));
    edge_list = g->hashArray[hashCode(e->start)].key->edges;
    head = edge_list->head;
    prev = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    }
    while (head) {
        if (edgeEquals(e, head->edge)) {
            if (prev) {
                prev->next = head->next;
            } else {
                edge_list->head = head->next;
            }
            return 0;
        }
        prev = head;
        head = head->next;
    }
    return -1;
}
*/
