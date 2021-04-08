#include <stdlib.h>
#include <stdio.h>
#include "../edge.c"
#include "print-functions.c"

int main() {
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1 = malloc(sizeof(struct Node));
    struct Node* n2 = malloc(sizeof(struct Node));
    struct Edge* e = malloc(sizeof(struct Edge));
    n1->data = hello;
    n1->visited = false;
    n1->id=id_num;
    id_num++;
    n2->data = goodbye;
    n2->visited = false;
    n2->id=id_num;
    id_num++;
    
    e->weight = 15.3;
    e->start = n1;
    e->end=n2;
    printEdge(e);

    printNode(start(e));
    printNode(end(e));
    printf("%f\n", weight(e));

    updateEdge(1.2, e);
    printf("New weight: %f\n", weight(e));

    return 0;
}
