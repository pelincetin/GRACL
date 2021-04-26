#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main()
{
    //Make two nodes 
    struct Graph* g = createGraph(100);
    char greeting[] = "Hello\n";
    char nodedata1[] = "noded1";
    char nodedata2[] = "noded2";
    //char goodbye[] = "Goodbye\n";
    struct Node* node1 = createNode(g, nodedata1);
    struct Node* node2 = createNode(g, nodedata2);
    struct Node* nodeh = createNode(g, greeting);  
    bool success = true;

    struct NodeList* nl = createNodeList();
    if (!empty_NL(nl)) {
        success = false;
    }

    appendNode(nl, node1);
    if (!(length_NL(nl) == 1)) {
        success = false;
    }
    prependNode(nl, node2);
    if (!(length_NL(nl) == 2)) {
        success = false;
    }
    if (!includesNode(nl, node2)) {
        success = false;
    }
    if (!includesNode(nl, node1)) {
        success = false;
    }

    removeFirst_NL(nl);
    if (!includesNode(nl, node1)) {
        success = false;
    }
    if (includesNode(nl, node2)) {
        success = false;
    }

    prependNode(nl, node2);
    removeLast_NL(nl);   
    if (!includesNode(nl, node2)) {
        success = false;
    }
    if (includesNode(nl, node1)) {
        success = false;
    }

    appendNode(nl, node1);
    appendNode(nl, nodeh);
    removeNode(nl, node1);
    removeNode(nl, nodeh);
    removeNode(nl, node2);
    if (!empty_NL(nl)) {
        success = false;
    }

    struct Node* node3 = createNode(g, "A");
    struct Node* node4 = createNode(g, "B");
    struct Node* node5 = createNode(g, "C");  
    appendNode(nl, node3);
    appendNode(nl, node4);
    appendNode(nl, node5);

    removeNodeGraph(g, node4);
    removeNode(nl, node4);
    //appendNode(nl, node4);
    //prependNode(nl, node4);
    removeNodeGraph(g, node3); 
    //neighbors(node3);
    if (!includesNode(nl, node3)) {
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
