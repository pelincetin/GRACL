#include <stdlib.h>
#include <stdio.h>
#include "../nodelist.c"
#include "print-functions.c"

int main()
{
    //Make two nodes 
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
    printf("Length should be 2: %d\n", length_NL(nl));

    removeFirst_NL(nl);
    printf("After remove first (list should be hello): ");
    printNodeList(nl);
    printf("\n");

    printf("Prepend Node 'goodbye'\n");
    prependNode(nl, n2);
    removeLast_NL(nl);
    printf("After remove last (list should be goodbye): ");
    printNodeList(nl);
    printf("\n");

    printf("Append node 'hello'\n");
    appendNode(nl, n1);
    removeNode(nl, n1);
    printf("After remove node hello (list should be goodbye): ");
    printNodeList(nl); 
    printf("\n");

    return 0;
}
