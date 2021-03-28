#include <stdlib.h>
#include <stdio.h>
#include "edge.h"

int main()
{
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1;
    struct Node* n2;
    n1 = createNode(hello);
    n2 = createNode(goodbye);

    struct Edge* e;
    e = addEdge(n1, n2, 15.3);
    printEdge(e);

    printNode(start(e));
    printNode(end(e));
    printf("%f\n", weight(e));

    updateEdge(1.2, e);
    printf("New weight: %f\n", weight(e));

    return 0;
}