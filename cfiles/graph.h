#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "commonFunctions.h"

// the key is going to be node
// the value would a nodelist whose edges  point to the key
struct Graph* createGraph(){
    struct Graph* graph;
    graph->hashArray = malloc(sizeof(struct DataItem) * SIZE);
    return graph;
}

int hashCode(struct Node* node) {
    int id_node = node->id;
    return id_node % SIZE;
}

void incrementId(){
    id_num++;
}

/*
struct NodeList* nodes(struct Graph* g){
    struct NodeList* nodes = malloc(sizeof(struct NodeList));
}
*/

struct Node* createNode(struct Graph* g, char* data) {
    struct Node* node = malloc(sizeof(struct Node));
    struct EdgeList* edge_list = malloc(sizeof(struct EdgeList));
    struct NodeList* nl = malloc(sizeof(struct NodeList));
    node->data = data;
    node->visited = false;
    node->id = id_num;
    node->edges = edge_list;
    incrementId();
    g->hashArray[hashCode(node)].value = nl;
    if (pthread_mutex_init(&node->lock, NULL) !=0) {
        fprintf(stderr, "createNode: Failure to initialize mutex\n");
        exit(1); 
    } else {
        return node;
    }
}

int removeEdge_G(struct Graph* g, struct Edge* e) {
    struct EdgeList* edge_list = g->hashArray[hashCode(e->start)].key->edges;
    struct EdgeListItem* head = edge_list->head;
    struct EdgeListItem* prev = NULL;
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

