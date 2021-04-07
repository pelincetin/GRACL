#include <stdlib.h>
#include <stdio.h>
#include "../graph.c"

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

int main() {
    struct Node* temp = malloc(sizeof(struct Node));
    struct Node* temp2 = malloc(sizeof(struct Node));
    struct NodeList* temp3 = malloc(sizeof(struct NodeList));
    struct Graph* g = malloc(sizeof(struct Graph));
    struct Edge* e = malloc(sizeof(struct Edge));
    char hello[] = "Hello\n";
    char goodbye[] = "Goodbye\n";
    
    g = createGraph();
    temp = createNode(g, hello);
    temp2 = createNode(g, goodbye);

    temp3 = nodes(g);
    printNodeList(temp3);

    //testing add edge
    e = addEdge(g, temp, temp2, 1.0);
    printEdge(e);
    printEdgeList(temp->edges);

    //testing neighbors()
    struct NodeList* neigh = malloc(sizeof(struct NodeList));
    neigh = neighbors(temp);
    printNodeList(neigh);

    // merge all files into one
    // edit the makefiles
    // implement removeNode
    // test removeNode
    // implement addEdge
    // implement removeEdge
    // test removeEdge
    
    return 0;
}
