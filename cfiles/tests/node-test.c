#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main() {
    printf("enters main");
    // create graph with 2 nodes and test the functions 
    struct Graph* g = createGraph(100);
    char greeting[] = "Hello\n";
    char nodedata1[] = "noded1";
    char nodedata2[] = "noded2";
    struct Node* node1 = createNode(g, nodedata1);
    struct Node* node2 = createNode(g, nodedata2);
    bool success = false;
    printf("gets here 0");

    // test data function 
    if (!(strcmp(data(node1), "noded1") && strcmp(data(node2), "noded2"))) {
        success = true;
    }

    // test update data function 
    node1 = updateData(greeting, node1);
    if ((strcmp(node1->data, "Hello\n") != 0)) {
        success = false; 
    }
    printf("gets here 1");

    // test visited function, that nodes are initialized to false
    if (visited(node1)) {
        success = false;
    }

    // test update visited 
    if (!visited(updateVisited(true, node1))) {
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
    if (cost(node1) != 0) {
        success = false;
    }
    incrementCost(node1);
    if (cost(node1) != 1) {
        success = false;
    }
    decrementCost(node1);
    if (cost(node1) != 0) {
        success = false;
    }
    updateCost(node1, 5);
    if (cost(node1) != 5) {
        success = false;
    }

    // test the two precursors 
    if (prec(node1)) { // should be null when inited
        success = false;
    }
    node1 = set_prec(node1, node2);
    if (strcmp(data(prec(node1)), "noded2")) {
        success = false;
    } 

    // test edges function 

    if (success) {
        printf("SUCCESS");
    } else {
        printf("FAILURE");
    }
}
