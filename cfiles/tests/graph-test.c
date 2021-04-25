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
    struct Edge* e4;
    struct Edge* e5;
    struct Edge* e6;
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
    e4 = addEdge(g, node2, node3, 43.0);
    e5 = addEdge(g, node3, node2, 43.0);
    e6 = addEdge(g, node3, node1, 43.0);

    printf("printing neighbors for node 1\n");
    printf("should be goodbye, ahmed\n");
    printNodeList(neighbors(node1));
    printf("printing neighbors for node 2\n");
    printf("should be hello, ahmed\n");
    printNodeList(neighbors(node2));
    printf("printing neighbors for node 3\n");
    printf("should be goodbye, hello\n");
    printNodeList(neighbors(node3));

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

    printf("after removing node3\n");
    printf("printing neighbors for node 1\n");
    printf("should be goodbye\n");
    printNodeList(neighbors(node1));
    printf("printing neighbors for node 2\n");
    printf("should be hello\n");
    printNodeList(neighbors(node2));


    removeEdgeGraph(g, e1);
    if (!empty_EL(edges(node1))) {
        success = false;
    }  
    printf("after removing edge1\n");
    printf("printing neighbors for node 1\n");
    printf("should be nothing\n");
    printNodeList(neighbors(node1));
    printf("printing neighbors for node 2\n");
    printf("should be hello\n");
    printNodeList(neighbors(node2));

    removeNodeGraph(g, node2);
    printf("after removing node2\n");
    printf("printing neighbors for node 1\n");
    printf("should be nothing\n");
    printNodeList(neighbors(node1));
    printf("printing edges for node 1\n");
    printf("should be nothing\n");
    printEdgeList(edges(node1));
    printf("printing nodes for graph g \n");
    printf("should be hello\n");
    printNodeList(nodes(g)); // should print Hello

    //addEdge(g, node1, node2, 5.0); // this line causes a segfault
    removeNodeGraph(g, node1);
    if (!(empty_NL(nodes(g)) == 1)) {
        success = false;
    }

    printf("printing nodes for graph g after removing node 1\n");
    printNodeList(nodes(g)); // should print Hello

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
