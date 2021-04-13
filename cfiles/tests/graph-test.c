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

    if (success) {
        printf("SUCCESS\n");
    } else {
        printf("FAILURE\n");
    }
/*
    printf("expecting hello goodbye \n");
    printEdge(e1);
    printf("\n");
    printf("expecting goodbye hello \n");
    printEdge(e2);
    printf("\n");
    printEdgeList(node1->edges);

    nl2 = neighbors(node1);   
    printNodeList(nl2);

    //remove edge
    printf("Testing RemoveEdgeGraph\n");
    int x = removeEdgeGraph(g, e1);
    printf("Now I should print 0\n");
    printf("%d\n", x);
    //test if nodes remain same
    nl1 = nodes(g);
    printf("Should print hello goodbye\n");
    printNodeList(nl1);
    printf("\n");
    
    //test if removed from neighbors
    printf("Should print null\n");
    nl2 = neighbors(node1);
    printNodeList(nl2);
    printf("\n");

    printf("Should print hello\n");
    nl2 = neighbors(node2);
    printNodeList(nl2);
    printf("\n");
    
    //removeNode
    printf("Testing RemoveNodeGraph\n");
    x = removeNodeGraph(g, node1);
    printf("should print 0: %d\n", x);
    nl1 = nodes(g);
    printf("should print goodbye\n");
    printNodeList(nl1);


    printf("Testing RemoveNodeGraph\n");
    x = removeNodeGraph(g, node2);
    printf("should print 0: %d\n", x);
    nl1 = nodes(g);
    printf("should print nothing\n");
    printNodeList(nl1);

    //add back nodes
    //test remove node while edges exist
    node1 = createNode(g, hello);
    node2 = createNode(g, goodbye);

    e1 = addEdge(g, node1, node2, 14.0);
    e2 = addEdge(g, node2, node1, 13.0);

    printf("Testing RemoveNodeGraph again\n");
    x = removeNodeGraph(g, node1);
    printf("should print 0: %d\n", x);
    nl1 = nodes(g);
    printf("should print goodbye\n");
    printNodeList(nl1);
    nl2 = neighbors(node2);
    printf("should print nothing\n");
    printNodeList(nl2);
    printf("should print nothing\n");
    printEdgeList( g->hashArray[hashCode(g, node2)].value); */

    return 0;
}
