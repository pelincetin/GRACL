#include <stdlib.h>
#include <stdio.h>
#include "../edgelist.h"

void printEdgeList(struct EdgeList* edge_list) {
    struct EdgeListItem *current;
    current = edge_list->head;
    while (current != NULL) {
        printf("%s\n", current->edge->start->data); // Check each start node's data
        current = current->next;
    }
}

int main()
{
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1;
    struct Node* n2;
    n1 = createNode(hello);
    n2 = createNode(goodbye);

    struct Edge* e1;
    e1 = addEdge(n1, n2, 15.3);
    struct Edge* e2;
    e2 = addEdge(n2, n1, 3.7);

    struct EdgeList* el = createEdgeList();
    printf("Should be true: %s", empty(el) ? "true\n" : "false\n");

    printf("Append edge with start 'hello'\n");
    appendEdge(el, e1);
    printf("Prepend edge with start 'goodbye'\n");
    prependEdge(el, e2);
    printf("List should be goodbye hello: ");
    printEdgeList(el);
    printf("Length should be 2: %d\n", length(el));

    removeFirst(el);
    printf("After remove first (list should be hello): ");
    printEdgeList(el);
    printf("\n");

    printf("Prepend edge with start 'goodbye'\n");
    prependEdge(el, e2);
    removeLast(el);
    printf("After remove last (list should be goodbye): ");
    printEdgeList(el);
    printf("\n");

    printf("Append edge with start 'hello'\n");
    appendEdge(el, e1);
    removeEdge(el, e1);
    printf("After remove edge with start hello (list should be goodbye): ");
    printEdgeList(el); 
    printf("\n");

    return 0;
}