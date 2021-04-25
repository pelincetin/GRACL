#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"


int main() {
    struct Node* node1;
    struct Node* node2;
    struct Node* node3;
    struct Edge* e1;
    struct Edge* e2;
    struct Edge* e3;
    struct Edge* e4;
    struct Edge* e5;
    struct Edge* e6;
    struct Edge* e7;
    struct Edge* e8;
    struct Edge* e9;
    struct Edge* e10;
    struct Edge* e11;
    struct NodeList* nl1;
    struct Graph* g;
    struct NodeList* nl2;
    bool success = true;
    
    g = createGraph(3);
    node1 = createNode(g, "A");
    node2 = createNode(g, "B");
    node3 = createNode(g, "C");

    // add more than the size of the graph to make 
    // sure the size of the graph is doubled 
    struct Node* node4 = createNode(g, "D");
    struct Node* node5 = createNode(g, "E");
    struct Node* node6 = createNode(g, "F");
    struct Node* node7 = createNode(g, "G"); 
    struct Node* node8 = createNode(g, "H"); 

    nl1 = nodes(g);
    if (!(length_NL(nl1) == 8)) {
        success = false;
    }

    e1 = addEdge(g, node1, node2, 14.0);
    e2 = addEdge(g, node2, node1, 13.0);
    e3 = addEdge(g, node1, node3, 43.0);
    e4 = addEdge(g, node2, node3, 43.0);
    e5 = addEdge(g, node3, node2, 43.0);
    e6 = addEdge(g, node3, node1, 43.0);
    e7 = addEdge(g, node1, node8, 23.0);
    e8 = addEdge(g, node1, node7, 23.0);
    e9 = addEdge(g, node1, node6, 23.0);
    e10 = addEdge(g, node8, node4, 23.0);
    e11 = addEdge(g, node5, node4, 23.0);

    if (!(length_EL(edges(node1)) == 5)) {
        success = false;
    }

    removeNodeGraph(g, node3);
    //this line should break the program
    //struct EdgeList* el1 = edges(node3);
    //printEdgeList(el1);

    //this should break the program
    //double weight_e3 = weight(e3);
    //printf("%f", weight_e3);
    //double weight_e5 = weight(e5);
    //printf("%f", weight_e5);

    if (!(length_NL(neighbors(node1)) == 4)) {
        success = false;
    }
    if (!(length_EL(edges(node1)) == 4)) {
        success = false;
    }
    nl2 = nodes(g);
    if (!(length_NL(nl2) == 7)) {
        success = false;
    }

    removeEdgeGraph(g, e11);
    if (!empty_EL(edges(node5))) {
        success = false;
    }
    
    //addEdge(g, node1, node2, 5.0); // this line causes a MEM ERROR (CHECK FOR THIS)
    removeNodeGraph(g, node1);
    if (node1->id != 0) {
        success = false;
    }
    // Should print: edges: Node deleted
    //if (!empty_EL(edges(node1))) {
        //success = false;
    //}

    printNodeList(nodes(g)); 

    // what happens to node / edge after removed from graph
    removeNodeGraph(g, node2);
    removeNodeGraph(g, node4);
    removeNodeGraph(g, node5);
    removeNodeGraph(g, node6);
    removeNodeGraph(g, node7);
    removeNodeGraph(g, node8);
    if (!empty_NL(nodes(g))) {
        success = false;
    }

    //make an edge with two deleted nodes
    //make an edge with one deleted node

    // what if user adds back in node1? THEY CAN'T HA 
    node8 = createNode(g, "C");
    if (node8->id != 8) {
        success = false;
    }
    node7 = createNode(g, "H");
    e11 = addEdge(g, node8, node7, 23.0);
    //should print C
    printf("%s\n", data(start(e11)));
    // Remove the edge and make sure nothing happened to the node
    removeEdgeGraph(g, e11);
    //this should break the program
    //printf("%s\n", data(start(e11)));
    printf("%s\n", data(node7));

    //should break the program because the nodes are deleted
    //e11 = addEdge(g, node5, node4, 23.0);

    printNodeList(nodes(g)); 

    //this will break bc this is already deleted
    //removeNodeGraph(g, node3);
    //remove the same node twice

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
