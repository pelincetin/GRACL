#include <stdlib.h>
#include <string.h>

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
    return;
}

void printEdge (struct Edge* edge) {
    printf("Start node: %s", edge->start->data);
    printf("End node: %s", edge->end->data);
    printf("Weight: %f", edge->weight);
}

void printEdgeList (struct EdgeList* edge_list) {
    struct EdgeListItem* current;
    current = edge_list->head;
    while (current != NULL) {
        printf("%s\n", current->edge->start->data); // Check each start node's data
        current = current->next;
    }
    return;
}
