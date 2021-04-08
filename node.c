#include <stdlib.h>
#include <stdio.h>
#include "lockedobject.h"
#include <pthread.h>

bool nodeEquals(struct Node* node1, struct Node* node2)
{
    if (node1->id == node2->id) {
        return true;
    }
    return false;
}

int hashCode(struct Node* node) {
    int id_node = node->id;
    return id_node % SIZE;
}

bool edgeEquals(struct Edge* e1, struct Edge* e2) {
    return (((e1->weight == e2->weight) && nodeEquals(e1->start, e2->start)) && nodeEquals(e1->end, e2->end));
}

bool empty_NL(struct NodeList* node_list) {
    struct NodeListItem* current;
    current = node_list->head;
    return (current == NULL);
}

bool empty_EL(struct EdgeList* edge_list) {
    struct EdgeListItem *current;
    current = edge_list->head;
    return (current == NULL);
}

int length_EL(struct EdgeList* edge_list) {
    int length = 0;
    struct EdgeListItem *current;
    current = edge_list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int length_NL(struct NodeList* node_list) {
    int length = 0;
    struct NodeListItem *current;
    current = node_list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

struct NodeListItem* createNodeListItem(struct Node* e) {
    struct NodeListItem* item = malloc(sizeof(struct NodeListItem));
    item->node = e;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

void appendNode(struct NodeList* node_list, struct Node* n) {
    struct NodeListItem* new_last = createNodeListItem(n);
    if (!empty_NL(node_list)) {
        // if list not empty;
        new_last->prev = node_list->tail;
        struct NodeListItem* old_last = malloc(sizeof(struct NodeListItem));
        old_last = node_list->tail;
        old_last->next = new_last;
        node_list->tail = new_last;
    } else {
        // if list is empty;
        node_list->head = new_last;
        node_list->tail = new_last;
    }
    return;
}

struct EdgeListItem* createEdgeListItem(struct Edge* e) {
    struct EdgeListItem* item = malloc(sizeof(struct EdgeListItem));
    item->edge = e;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

void appendEdge(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem* new_last = createEdgeListItem(e);
    if (!empty_EL(edge_list)) {
        // if list not empty;
        new_last->prev = edge_list->tail;
        struct EdgeListItem *old_last;
        old_last = edge_list->tail;
        old_last->next = new_last;
        edge_list->tail = new_last;
    } else {
        // if list is empty;
        edge_list->head = new_last;
        edge_list->tail = new_last;
    }
    return;
}

int removeEdge(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem* head = edge_list->head;
    struct EdgeListItem* prev = NULL;
    struct EdgeListItem* next = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    } else {
        prev = head->prev;
        while (head) {
            if (edgeEquals(e, head->edge)) {
                if (prev) {
                    next = head->next;
                    prev->next = next;
                    if (next) {
                        next->prev = prev;
                    }
                } else {
                    next = head->next;
                    edge_list->head = next;
                    if (next) {
                        next->prev = NULL;
                    }
                }
                return 0;
            }
            prev = head;
            head = head->next;
        }
        return -1;
    }
}

int removeNode(struct NodeList* node_list, struct Node* e) {
    struct NodeListItem* head = node_list->head;
    struct NodeListItem* prev = NULL;
    struct NodeListItem* next = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    } else {
        prev = head->prev;
        while (head) {
            if (nodeEquals(e, head->node)) {
                if (prev) {
                    next = head->next;
                    prev->next = next;
                    if (next) {
                        next->prev = prev;
                    }
                } else {
                    next = head->next;
                    node_list->head = next;
                    if (next) {
                        next->prev = NULL;
                    }
                }
                return 0;
            }
            prev = head;
            head = head->next;
        }
        return -1;
    }
} 

/* New start and end accessors */
struct Node* start(struct Edge* edge) {
    return edge->start;
}

struct Node* end(struct Edge* edge) {
    return edge->end;
}


void incrementId(){
    id_num++;
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

void printNode (struct Node* node) {
    printf("%s\n", node->visited ? "true" : "false");
    printf("%d\n", node->id);
    printf("%s\n", node->data);
}

const char* data(struct Node* node)
{
    return node->data;
}

/* Return the NodeList of surrounding neighbors 
 * NodeList type not defined yet though
NodeList neighbors(struct Node* node)
{
    struct EdgeList* edges = node->edges;

    for (edge in edges) {

    }
    return neighbors; 
}
*/

/* Return the edgelist of surrounding edges */
struct EdgeList* edges(struct Node* node)
{
    return node->edges; 
}


/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct Node* node)
{
    return node->visited;
}

struct Node* updateData(struct Node* node, char* new_data)
{
    node->data = new_data;
    return node;
}

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(struct Node* node, bool tf)
{
    node->visited = tf;
    return node;
}

/*
int main(){
    //struct Node* n = createNode("blah");
    //nodeEquals(n, n);
    return 0;
}
*/