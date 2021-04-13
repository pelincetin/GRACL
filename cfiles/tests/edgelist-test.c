#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main() {
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    char yo[] = "Yo\n";
    struct Node* n1 = malloc(sizeof(struct Node));
    struct Node* n2 = malloc(sizeof(struct Node));
    struct Node* n3 = malloc(sizeof(struct Node));
    struct Edge* e1 = malloc(sizeof(struct Edge));
    struct Edge* e2 = malloc(sizeof(struct Edge));
    struct Edge* e3 = malloc(sizeof(struct Edge));
    
    n1->data = hello;
    n1->visited = false;
    n1->id=id_num;
    id_num++;

    n2->data = goodbye;
    n2->visited = false;
    n2->id=id_num;
    id_num++;

    n3->data = yo;
    n3->visited = false;
    n3->id=id_num;
    id_num++;

    e1->weight = 15.3;
    e1->start = n1;
    e1->end = n2;
    
    e2->weight = 3.7;
    e2->start = n2;
    e2->end = n1;

    e3->weight = 4.8;
    e3->start = n3;
    e3->end = n2;

    struct EdgeList* el = createEdgeList();
    printf("Should be true: %s", empty_EL(el) ? "true\n" : "false\n");

    printf("Append edge with start 'hello'\n");
    appendEdge(el, e1);
    printf("Prepend edge with start 'goodbye'\n");
    prependEdge(el, e2);
    printf("List should be goodbye hello: \n");
    printEdgeList(el);
    printf("Length should be 2: %d\n", length_EL(el));
    prependEdge(el, e3);
    printf("List should be yo goodbye hello: \n");
    printEdgeList(el);
    
    removeFirst_EL(el);
    printf("After remove first (list should be goodbye hello): ");
    printEdgeList(el);
    printf("\n");

    printf("Prepend edge with start 'yo'\n");
    prependEdge(el, e3);
    removeLast_EL(el);
    printf("After remove last (list should be yo goodbye): ");
    printEdgeList(el);
    printf("\n");

    printf("Append edge with start 'hello'\n");
    appendEdge(el, e1);
    removeEdge(el, e1);
    printf("After remove edge with start hello (list should be yo goodbye): ");
    printEdgeList(el); 
    printf("\n");

    removeFirst_EL(el);
    printf("After remove first (list should be goodbye ): ");
    printEdgeList(el);
    printf("\n");

    removeFirst_EL(el);
    printf("After remove first (list should be empty): ");
    printEdgeList(el);
    printf("\n");

    return 0;
}
