#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main()
{
    //Make two nodes 
<<<<<<< HEAD
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
=======
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1 = malloc(sizeof(struct Node));
    struct Node* n2 = malloc(sizeof(struct Node));
    n1->data = hello;
    n1->visited = false;
    n1->id=id_num;
    id_num++;
    n2->data = goodbye;
    n2->visited = false;
    n2->id=id_num;
    id_num++;

    struct NodeList* nl = createNodeList();
    printf("Should be true: %s", empty_NL(nl) ? "true\n" : "false\n");
    printf("Append node 'hello'\n");
    appendNode(nl, n1);
    printf("Prepend node 'goodbye'\n");
    prependNode(nl, n2);
    printf("List should be goodbye hello: ");
    printNodeList(nl);
    printf("Data of head should be goodbye: %s\n", head_NL(nl)->data);
    printf("Data of tail should be hello: %s\n", tail_NL(nl)->data);
    printf("Length should be 2: %d\n", length_NL(nl));
>>>>>>> graph-algos

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

    if (success) {
        printf("SUCCESS\n");
    }
    else {
        printf("FAILURE\n");
    }

    return 0;
}
