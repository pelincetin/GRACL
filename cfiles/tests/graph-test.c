#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"


int main() {
    struct Node* node1;
    struct Node* node2;
    struct Edge* e1;
    struct Edge* e2;
    struct NodeList* nl1;
    struct Graph* g;
    struct NodeList* nl2;
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    
    g = createGraph(100);
    node1 = createNode(g, hello);
    node2 = createNode(g, goodbye);

    nl1 = nodes(g);
    printNodeList(nl1);

    e1 = addEdge(g, node1, node2, 14.0);
    e2 = addEdge(g, node2, node1, 13.0);

    printEdge(e1);
    printEdge(e2);
    printEdgeList(node1->edges);

    nl2 = neighbors(node1);   
    printNodeList(nl2);

    int x = removeEdgeGraph(g, e1);
    printf("Now I should print 0\n");
    printf("%d\n", x);

    x = removeNodeGraph(g, node1);
    printf("%d\n", x);

    x = removeNodeGraph(g, node2);
    printf("%d\n", x);

    return 0;
}
