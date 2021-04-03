#include <stdlib.h>
#include <stdio.h>
#include "../edge.h"

void printEdge (struct Edge* edge) {
    printf("Start node: %s", edge->start->data);
    printf("End node: %s", edge->end->data);
    printf("Weight: %f", edge->weight);
}

void printNode (struct Node* node) {
    printf("%s", node->visited ? "true\n" : "false\n");
    printf("%d", node->id);
    printf("%s", node->data);
}

int main() {
    //Make two nodes to be start and end for edge
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    struct Node* n1 = NULL;
    struct Node* n2 = NULL;
    n1->data = hello;
    n1->visited = false;
    n1->id=id_num;
    id_num++;
    n2->data = goodbye;
    n2->visited = false;
    n2->id=id_num;
    id_num++;
    
    struct Edge* e;
    e = addEdge(n1, n2, 15.3);
    printEdge(e);

    printNode(start(e));
    printNode(end(e));
    printf("%f\n", weight(e));

    updateEdge(1.2, e);
    printf("New weight: %f\n", weight(e));

    return 0;
}