#include <stdlib.h>
#include <stdio.h>
#include "lockedobject.h"
#include <pthread.h>

void incrementId(){
    id_num++;
}

// SHOULD GO IN GRAPH EVENTUALLY!
struct Node* createNode(char* data) {
    struct Node* node = malloc(sizeof(struct Node));
    struct EdgeList* edge_list = malloc(sizeof(struct EdgeList));
    node->data = data;
    node->visited = false;
    node->id = id_num;
    node->edges = edge_list;
    incrementId();
    if (pthread_mutex_init(&node->lock, NULL) !=0) {
        fprintf(stderr, "createNode: Failure to initialize mutex\n");
        exit(1); 
    }
    else {
        return node;
    }
};

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

struct Node* updateData(char* new_data, struct Node* node)
{
    node->data = new_data;
    return node;
}

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(bool tf, struct Node* node)
{
    node->visited = tf;
    return node;
}

/* Compares the two Node objects by id 
 * Returns True if they are the same and returns False if not */
bool nodeEquals(struct Node* node1, struct Node* node2)
{
    if (node1->id == node2->id) {
        return true;
    }
    return false;
}
/*
int main(){
    struct Node* n = createNode("blah");
    printNode(n);
    return 0;
}
*/
