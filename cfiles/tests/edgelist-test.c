#include <stdlib.h>
#include <stdio.h>
#include "../edgelist.c"

void printEdgeList (struct EdgeList* edge_list) {
    struct EdgeListItem* current;
    current = edge_list->head;
    while (current != NULL) {
        printf("%s\n", current->edge->start->data); // Check each start node's data
        current = current->next;
    }
    return;
}

int main() {
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1 = malloc(sizeof(struct Node));
    struct Node* n2 = malloc(sizeof(struct Node));
    struct Edge* e1 = malloc(sizeof(struct Edge));
    struct Edge* e2 = malloc(sizeof(struct Edge));
    n1->data = hello;
    n1->visited = false;
    n1->id=id_num;
    id_num++;
    n2->data = goodbye;
    n2->visited = false;
    n2->id=id_num;
    id_num++;

    e1->weight = 15.3;
    e1->start = n1;
    e1->end = n2;
    
    e2->weight = 3.7;
    e2->start = n2;
    e2->end = n1;

    struct EdgeList* el = createEdgeList();
    printf("Should be true: %s", empty_EL(el) ? "true\n" : "false\n");

    printf("Append edge with start 'hello'\n");
    appendEdge(el, e1);
    printf("Prepend edge with start 'goodbye'\n");
    prependEdge(el, e2);
    printf("List should be goodbye hello: \n");
    printEdgeList(el);
    printf("Weight of head should be 3.7: %f\n", head_EL(el)->weight);
    printf("Weight of tail should be 15.3: %f\n", tail_EL(el)->weight);
    printf("Length should be 2: %d\n", length_EL(el));
    
    removeFirst_EL(el);
    printf("After remove first (list should be hello): ");
    printEdgeList(el);
    printf("\n");

    printf("Prepend edge with start 'goodbye'\n");
    prependEdge(el, e2);
    removeLast_EL(el);
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
