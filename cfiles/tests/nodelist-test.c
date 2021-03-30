#include <stdlib.h>
#include <stdio.h>
#include "../nodelist.h"

void printNodeList(struct NodeList* node_list) {
    struct NodeListItem *current;
    current = node_list->head;
    while (current != NULL) {
        printf("%s\n", current->node->data); 
        current = current->next;
    }
}

int main()
{
    //Make two nodes 
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1;
    struct Node* n2;
    n1 = createNode(hello);
    n2 = createNode(goodbye);

    
    struct NodeList* nl = createNodeList();
    printf("Should be true: %s", empty(nl) ? "true\n" : "false\n");
    printf("Append node 'hello'\n");
    appendNode(nl, n1);
    printf("Prepend node 'goodbye'\n");
    prependNode(nl, n2);
    printf("List should be goodbye hello: ");
    printNodeList(nl);
    printf("Length should be 2: %d\n", length(nl));

    removeFirst(nl);
    printf("After remove first (list should be hello): ");
    printNodeList(nl);
    printf("\n");

    printf("Prepend Node 'goodbye'\n");
    prependNode(nl, n2);
    removeLast(nl);
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