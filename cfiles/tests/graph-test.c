#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"


int main() {

    // test neighbors
    // test edges as well as graph functions

    /* graph functions
     * addEdge
     * removeNodeGraph
     * removeEdgeGraph
     * createNode
     * nodes
     * incrementId
     * hashCode
     * createGraph
     */

    struct Node* node1;
    struct Node* node2;
    struct Node* node3;
    struct Edge* e1;
    struct Edge* e2;
    struct Edge* e3;
    struct NodeList* nl1;
    struct Graph* g;
    struct NodeList* nl2;
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    char ahmed[] = "ahmed\n";
    bool success = true;
    
    g = createGraph(100);
    node1 = createNode(g, hello);
    node2 = createNode(g, goodbye);
    node3 = createNode(g, ahmed);

    nl1 = nodes(g);
    if (!(length_NL(nl1) == 3)) {
        success = false;
    }

    e1 = addEdge(g, node1, node2, 14.0);
    e2 = addEdge(g, node2, node1, 13.0);
    e3 = addEdge(g, node1, node3, 43.0);

    printNodeList(neighbors(node1));

    if (!(length_EL(edges(node1)) == 2)) {
        success = false;
    }

    removeNodeGraph(g, node3);
    if (!(length_NL(neighbors(node1)) == 1)) {
        success = false;
    }    
    if (!(length_EL(edges(node1)) == 1)) {
        success = false;
    }
    nl2 = nodes(g);
    if (!(length_NL(nl2) == 2)) {
        success = false;
    }  

    removeEdgeGraph(g, e1);
    if (!empty_EL(edges(node1))) {
        success = false;
    }  

    removeNodeGraph(g, node2);
    printNodeList(nodes(g)); // should print Hello
    printEdgeList(edges(node1)); // should print nothing

    //addEdge(g, node1, node2, 5.0); // this line causes a segfault
    removeNodeGraph(g, node1);
    if (!(empty_NL(nodes(g)) == 1)) {
        success = false;
    }

    // test making an graph with a size of 0 or smaller
    //struct Graph* g2 = createGraph(0);
    //struct Graph* g3 = createGraph(-1);

    if (success) {
        printf("SUCCESS\n");
    } else {
        printf("FAILURE\n");
    }

    return 0;
}
