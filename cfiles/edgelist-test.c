#include <stdlib.h>
#include <stdio.h>
#include "edgelist.h"

int main()
{
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1;
    struct Node* n2;
    n1 = createNode(hello);
    n2 = createNode(goodbye);

    struct Edge* e1;
    e1 = addEdge(n1, n2, 15.3);
    printEdge(e1);
    printf("\n");
    struct Edge* e2;
    e2 = addEdge(n2, n1, 3.7);
    printEdge(e2);
    printf("\n");

    struct EdgeList* el = createEdgeList();
    printf("Should be empty: %s", empty(el) ? "true\n" : "false\n");
    appendEdge(el, e1);
    prependEdge(el, e2);
    printEdgeList(el);
    printf("\nLength should be 2: %d\n", length(el));

    removeFirst(el);
    printf("after remove first: ");
    printEdgeList(el);
    printf("\n");

    prependEdge(el, e2);
    // printEdge(el->tail->edge);
    printf("Should be false: %s", (el->tail ==NULL) ? "true\n" : "false\n");
    removeLast(el);
    printf("after remove last: \n");
    printEdgeList(el);
    removeEdge(el, e1);
    printf("after remove edge: ");
    printEdgeList(el); 
    printf("\n");

    return 0;
}