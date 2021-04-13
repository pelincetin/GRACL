#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main() {
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    char yo[] = "Yo\n";
    struct Graph* g = createGraph(100);
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
<<<<<<< HEAD
    if (!(length_EL(el)==2)) {
        success = false; 
    }
    prependEdge(el, e3);
    if (!(length_EL(el)==3)) {
        success = false; 
    }
=======
    printf("List should be goodbye hello: \n");
    printEdgeList(el);
    printf("Weight of head should be 3.7: %f\n", head_EL(el)->weight);
    printf("Weight of tail should be 15.3: %f\n", tail_EL(el)->weight);
    printf("Length should be 2: %d\n", length_EL(el));
>>>>>>> graph-algos
    
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

    if (success) {
        printf("SUCCESS\n");
    }
    else {
        printf("FAILURE\n");
    }

    return 0;
}
