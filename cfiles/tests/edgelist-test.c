#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main() {
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    char yo[] = "Yo\n";
    struct Graph* g = createGraph(2);
    struct Node* n1 = createNode(g, hello);
    struct Node* n2 = createNode(g, goodbye);
    struct Node* n3 = createNode(g, yo);
    struct Edge* e1 = addEdge(g, n1, n2, 15.3);
    struct Edge* e2 = addEdge(g, n2, n1, 3.7);
    struct Edge* e3 = addEdge(g, n3, n2, 4.8);
    bool success = true;

    struct EdgeList* el = createEdgeList();
    if (!empty_EL(el)) {
        success = false; 
    }

    appendEdge(el, e1);
    prependEdge(el, e2);
    if (!(length_EL(el)==2)) {
        success = false; 
    }

    prependEdge(el, e3);
    if (!(length_EL(el)==3)) {
        success = false; 
    }
    
    removeFirst_EL(el);
    printf("After remove first (list should be goodbye hello): ");
    printEdgeList(el);
    printf("\n");
    if (!(length_EL(el)==2)) {
        success = false; 
    }

    prependEdge(el, e3);
    removeLast_EL(el);
    printf("After remove last (list should be yo goodbye): ");
    printEdgeList(el);
    printf("\n");
    if (!(length_EL(el)==2)) {
        success = false; 
    }

    removeEdge(el, e1);
    printf("After remove edge (list should be yo goodbye): ");
    printEdgeList(el); 
    printf("\n");
    if (!(length_EL(el)==2)) {
        success = false; 
    }

    removeEdge(el, e2);
    if (!(length_EL(el)==1)) {
        success = false; 
    }

    removeEdge(el, e3);
    if (!empty_EL(el)) {
        success = false; 
    }

    struct Edge* e4 = addEdge(g, n3, n2, 4.8);
    struct Edge* e5 = addEdge(g, n2, n3, 4.8);
    struct Edge* e6 = addEdge(g, n1, n2, 4.8);
    appendEdge(el, e4);
    appendEdge(el, e5);
    appendEdge(el, e6);
    removeEdgeGraph(g, e4);
    printEdge(head_EL(el));
    printf("\n");

    removeFirst_EL(el);
    //Breaks the program, should print prependEdge: Edge  deleted
    //prependEdge(el, e4);

    //Breaks the program, should print appendEdge: Edge  deleted
    //appendEdge(el, e4);
    printEdge(head_EL(el));
    printf("\n");

    removeEdge(el, e5);
    printEdge(tail_EL(el));
    printf("\n");

    removeEdge(el, e6);

    //this will give an error because it's empty
    //printEdge(head_EL(el));

    if (success) {
        printf("SUCCESS\n");
    }
    else {
        printf("FAILURE\n");
    }

    return 0;
}
