#include <stdlib.h>
#include <stdio.h>
#include "../graph.c"
#include "print-functions.c"


int main() {
    struct Node* temp = malloc(sizeof(struct Node));
    struct Node* temp2 = malloc(sizeof(struct Node));
    struct Edge* e1 = malloc(sizeof(struct Edge));
    struct Edge* e2 = malloc(sizeof(struct Edge));
    struct NodeList* temp3 = malloc(sizeof(struct NodeList));
    struct Graph* g = malloc(sizeof(struct Graph));
    struct Edge* e = malloc(sizeof(struct Edge));
    struct NodeList* neigh = malloc(sizeof(struct NodeList));
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    
    g = createGraph();
    temp = createNode(g, hello);
    temp2 = createNode(g, goodbye);

    temp3 = nodes(g);
    printNodeList(temp3);

    e1 = addEdge(g, temp, temp2, 14.0);
    e2 = addEdge(g, temp2, temp, 13.0);

    printEdge(e1);
    printEdge(e2);
    printEdgeList(temp->edges);

    neigh = neighbors(temp);   
    printNodeList(neigh);

    int x = removeEdgeGraph(g, e1);
    printf("Now I should print 0\n");
    printf("%d\n", x);

    x = removeNodeGraph(g, temp);
    printf("%d\n", x);

    x = removeNodeGraph(g, temp2);
    printf("%d\n", x);

    return 0;
}
