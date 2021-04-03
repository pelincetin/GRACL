#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "commonFunctions.h"

const char* data(struct Node* node)
{
    return node->data;
}

/* Return the NodeList of surrounding neighbors 
 * NodeList type not defined yet though

iterate over the edgelist in the node struct
*/
struct NodeList* neighbors(struct Node* node)
{
    struct EdgeList* edges = node->edges;
    int length_of_edgelist = length_EL(edges);
    struct NodeList* neighbors = NULL;
    int i;

    for (i=0; i< length_of_edgelist; i++) {
        appendNode(neighbors, edges->head->edge->end);
    }
    return neighbors; 
}

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
