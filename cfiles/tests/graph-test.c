#include <stdlib.h>
#include <stdio.h>
#include "../graph.c"


void printNode (struct Node* node) {
    printf("%s\n", node->visited ? "true" : "false");
    printf("%d\n", node->id);
    printf("%s", node->data);
}

int main() {
    struct Node* temp = malloc(sizeof(struct Node));
    struct Node* temp2 = malloc(sizeof(struct Node));
    struct Edge* e1 = malloc(sizeof(struct Edge));
    struct NodeList* temp3 = malloc(sizeof(struct NodeList));
    struct Graph* g = malloc(sizeof(struct Graph));
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    
    g = createGraph();
    temp = createNode(g, hello);
    temp2 = createNode(g, goodbye);

    temp3 = nodes(g);
    printNodeList(temp3);

    e1 = addEdge(g, temp, temp2, 14.0);
    int x = removeNodeGraph(g, temp);
    printf("%d\n", x);

    //int x = removeEdgeGraph(g, e1);
    printf("Now I should print 0\n");
    //printf("%d\n", x);

    fprintf(stderr, "yo");
    //printf("%d\n", x);
    //x = removeNodeGraph(g, temp2);
    //printf("%d\n", x);


    // implement removeNode
    // test removeNode

    return 0;
}
