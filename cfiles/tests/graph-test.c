#include <stdlib.h>
#include <stdio.h>
#include "../graph.h"

void printNode (struct Node* node) {
    printf("%s\n", node->visited ? "true" : "false");
    printf("%d\n", node->id);
    printf("%s", node->data);
}

int main() {
    struct Graph* g = createGraph();
    temp = createNode(g, greeting);
    printNode(temp); 
}
