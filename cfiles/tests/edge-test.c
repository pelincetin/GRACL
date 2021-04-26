#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main() {
   // create graph with 2 nodes and test the functions 
    struct Graph* g = createGraph(100);
    char nodedata1[] = "noded1";
    char nodedata2[] = "noded2";
    char nodedata3[] = "noded3";

    struct Node* node1 = createNode(g, nodedata1);
    struct Node* node2 = createNode(g, nodedata2);
    struct Node* node3 = createNode(g, nodedata3);

    struct Edge* edge1 = addEdge(g, node1, node2, 1.7);
    struct Edge* edge2 = addEdge(g, node2, node3, 6.8);
    struct Edge* edge3 = addEdge(g, node1, node2, 1.7);

    bool success = true;

    char bits[] = {0, 0, 0, 0, 0, 0, 0xf0, 0x7f};
    double infinity = *(double*)bits;

    // test updateEdge and weight functions
    updateEdge(edge2, 16.3);
    if (edge2->weight != 16.300000) {
        success = false; 
    }
    updateEdge(edge2, 90.1);
    if (edge2->weight != 90.100000) {
        success = false; 
    }
    updateEdge(edge2, -90.1);
    if (edge2->weight != -90.100000) {
        success = false; 
    }
    updateEdge(edge2, infinity);
    if (edge2->weight != infinity) {
        success = false; 
    }
    
    // test edgeEquals
    if(edgeEquals(edge1, edge2)) {
        success = false;
    }
    if(!edgeEquals(edge1, edge1)) {
        success = false;
    }

    // test end and start functions
    if(strcmp(end(edge1)->data, start(edge2)->data) != 0) {
        success = false;
    }
    if(strcmp(start(edge1)->data, start(edge3)->data) != 0) {
        success = false;
    }
    if(strcmp(start(edge1)->data, end(edge1)->data) == 0) {
        success = false;
    }
    
    removeNodeGraph(g, node1);
    //start(edge1);
    //end(edge3);
    //updateEdge(edge1, 15.0);
    //double bad_dub = weight(edge3);
    double good_dub = weight(edge2);
    printf("%f\n", good_dub);
    removeNodeGraph(g, node3);
    //start(edge2);
    //double bad_dub2 = weight(edge2);
    //edgeEquals(edge1, edge2);

    if (success) {
        printf("SUCCESS\n");
    } else {
        printf("FAILURE\n");
    }
}
