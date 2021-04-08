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

int hashCode(struct Node* node);

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

void prependNode(struct NodeList* node_list, struct Node* e);

void appendNode(struct NodeList* node_list, struct Node* n);

void appendEdge(struct EdgeList* edge_list, struct Edge* e);

void prependEdge(struct EdgeList* edge_list, struct Edge* e);

void updateEdge(double new_weight, struct Edge* edge);

bool nodeEquals(struct Node* node1, struct Node* node2)
{
    if (node1->id == node2->id) {
        return true;
    }
    return false;
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
struct EdgeList* createEdgeList() {
    struct EdgeList* edge_list = malloc(sizeof(struct EdgeList));
    edge_list->head = NULL;
    edge_list->tail = NULL;
    return edge_list;
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

struct NodeList* createNodeList() {
    struct NodeList* node_list = malloc(sizeof(struct NodeList));
    node_list->head = NULL;
    node_list->tail = NULL;
    return node_list;
}

struct NodeList* neighbors(struct Node* node){
    struct EdgeList* edges = node->edges;
    struct NodeList* neighbors = createNodeList();
    struct EdgeListItem* current = edges->head;
    while (current != NULL) {
        appendNode(neighbors, current->edge->end);
        current = current->next;
    }
    return neighbors; 
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
        struct EdgeListItem *old_last = malloc(sizeof(struct EdgeListItem));
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

int includesNode(struct NodeList* nl, struct Node* n){
    struct NodeListItem* temp = malloc(sizeof(struct NodeListItem));
    if (nl != NULL){
        temp = nl->head;
    }else{
        return 0;
    }
    while(temp){
        if (n->id == temp->node->id){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
