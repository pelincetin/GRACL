#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main() {
    // NEED TO TEST NODE NEIGHBORS

    // create graph with 2 nodes and test the functions 
    struct Graph* g = createGraph(100);
    char greeting[] = "Hello\n";
    char nodedata1[] = "noded1";
    char nodedata2[] = "noded2";
    struct Node* node1 = createNode(g, nodedata1);
    struct Node* node2 = createNode(g, nodedata2);
    bool success = false;

    // test data function 
    if (!(strcmp(data(node1), "noded1") && strcmp(data(node2), "noded2"))) {
        success = true;
    }

    // test update data function 
    node1 = updateData(node1, greeting);
    if ((strcmp(node1->data, "Hello\n") != 0)) {
        success = false; 
    }

    // test visited function, that nodes are initialized to false
    if (visited(node1)) {
        success = false;
    }

    // test update visited 
    if (!visited(updateVisited(node1, true))) {
        success = false;
    }

    // test nodeequals
    if (!nodeEquals(node1, node1)) {
        success = false;
    }

    if (nodeEquals(node1, node2)) {
        success = false; 
    }
    // test the 4 cost functions
    if (cost(node1) != -1) {
        success = false;
    }
    incrementCost(node1);
    if (cost(node1) != 0) {
        success = false;
    }
    decrementCost(node1);
    if (cost(node1) != -1) {
        success = false;
    }
    updateCost(node1, 5);
    if (cost(node1) != 5) {
        success = false;
    }

    // test the two precursors 
    if (!prec(node1)) { // should be null when inited
        success = false;
    }
    node1 = setPrec(node1, node2);
    if (prec(node1) == NULL) {
        success = false;
    }
    const char* data1;
    if (prec(node1) == NULL) {
        success = false;
    }
    data1 = data(prec(node1));
    if (data1 == NULL) {
        success = false;
    }
    if (strcmp(data1, "noded2") != 0) {
        success = false;
    } 

    // test getEdge
    struct Edge* edge1 = addEdge(g, node1, node2, 1.7);
    struct Edge* edge2 = addEdge(g, node2, node1, 6.8);
    if (!edgeEquals(edge1, getEdge(node1, node2))) {
        success = false;
    }
    if (!edgeEquals(edge2, getEdge(node2, node1))) {
        success = false;
    }
    if (getEdge(node1, node1)) {
        success = false;
    }

    removeNodeGraph(g, node1);
    removeNodeGraph(g, node2);

    // these (as desired, error out)
    //struct Node* parent = prec(node1);
    //setPrec(node1, node2);
    //char* dat = data(node1);
    //bool vis = visited(node2);
    //struct Edgelist* edge = edges(node1);
    //double cost1 = cost(node2);
    //incrementCost(node2);
    //decrementCost(node1);
    //updateCost(node1, 3.0);
    //struct Edge* e = getEdge(node1, node2);
    //bool bad_test = nodeEquals(node1, node2);
    //updateVisited(node1, true);
    //updateData(node2, "hi");


    if (success) {
        printf("SUCCESS\n");
    } else {
        printf("FAILURE\n");
    }
}
