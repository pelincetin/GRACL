#include <stdlib.h>
#include <stdio.h>
#include "../graph.h"

void printNodeList(struct NodeList* node_list) {
    struct NodeListItem *current = malloc(sizeof(struct NodeListItem));
    current = node_list->head;
    while (current != NULL) {
        printf("%s\n", current->node->data); 
        current = current->next;
    }
}

void printNode (struct Node* node) {
    printf("%s\n", node->visited ? "true" : "false");
    printf("%d\n", node->id);
    printf("%s", node->data);
}

int main() {
    struct Node* temp = malloc(sizeof(struct Node));
    struct Node* temp2 = malloc(sizeof(struct Node));
    struct NodeList* temp3 = malloc(sizeof(struct NodeList));
    struct Graph* g = malloc(sizeof(struct Graph));
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    
    g = createGraph();
    temp = createNode(g, hello);
    temp2 = createNode(g, goodbye);

    temp3 = nodes(g);
    printNodeList(temp3);

    

    return 0;
}
