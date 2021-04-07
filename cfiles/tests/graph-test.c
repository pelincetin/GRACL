#include <stdlib.h>
#include <stdio.h>
#include "../graph.c"
#include "print-functions.c"


int main() {
    struct Node* temp = malloc(sizeof(struct Node));
    struct Node* temp2 = malloc(sizeof(struct Node));
    struct NodeList* temp3 = malloc(sizeof(struct NodeList));
    struct Graph* g = malloc(sizeof(struct Graph));
    struct Edge* e = malloc(sizeof(struct Edge));
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    
    g = createGraph();
    temp = createNode(g, hello);
    temp2 = createNode(g, goodbye);

    temp3 = nodes(g);
    printNodeList(temp3);

    //testing add edge
    e = addEdge(g, temp, temp2, 1.0);
    printEdge(e);
    printEdgeList(temp->edges);

    //testing neighbors()
    addEdge(g, temp, createNode(g, "Another"), 3);
    struct NodeList* neigh = malloc(sizeof(struct NodeList));
    neigh = neighbors(temp);   
    printNodeList(neigh);

    // merge all files into one
    // edit the makefiles
    // implement removeNode
    // test removeNode
    // implement addEdge
    // implement removeEdge
    // test removeEdge
    
    return 0;
}
