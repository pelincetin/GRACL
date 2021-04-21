#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

// Loosely based off of the Java implementation here: https://www.baeldung.com/java-dijkstra

// Find the unsettled node the shortest distance away
struct Node* getCheapestNode(struct NodeList* unsettledNodes) {
    struct Node* cheapestNode = NULL;
    double cheapestCost = 100000000000000000000000.0; // had trouble with infinity so going with this as max
    struct NodeListItem* current = unsettledNodes->head;
    while (current) {
        //printf("current node data (from getCheapestNode): %s\n", current->node->data);
        if (current->node->cost < cheapestCost) {
            cheapestCost = current->node->cost;
            //printf("cheapestCost: %f\n", cheapestCost);
            cheapestNode = current->node;
            //printf("cheapestNode data: %s\n", cheapestNode->data);
        }
        current = current->next;
    }
    return cheapestNode;
}

// Recurse through goal node's precursors to start node to get full path
struct NodeList* getShortestPath(struct Node* source, struct Node* goal) {
    fprintf(stderr, "made it to getShortestPath\n");
    struct NodeList* path = createNodeList();
    // printf("path head: %s\n", path->head->node->data);
    // printf("path tail: %s\n", path->tail->node->data);
    // if (path->head == NULL) {
    //         printf("path head is null\n");
    // }
    struct Node* current = goal;
    fprintf(stderr, "hey");
    while (current) {
        fprintf(stderr, "wtf is happening\n");
        // printf("current node data (from getShortestPath): %s\n", current->data);
        // printf("path head: %s\n", path->head->node->data);
        // printf("path tail: %s\n", path->tail->node->data);
        // printf("printing the path\n");
        // printNodeList(path);
        prependNode(path, current);
        
        // printf("printing the path after i prepend\n");
        // fprintf(stderr, "path\n");
        // printNodeList(path);
        // printf("\n");
        if (current->precursor) {
            current = current->precursor;
        }else{
            current = NULL;
        }
    }
    printNodeList(path);
    return path;
}

// Main Dijkstra method
struct NodeList* dijkstra(struct Graph* g, struct Node* source, struct Node* goal) {
    updateCost(source, 0);

    struct NodeList* settledNodes = createNodeList(); // Nodes with known cheapest cost
    //printf("settled nodes: ");
    //printNodeList(settledNodes);
    //printf("\n");
    struct NodeList* unsettledNodes = createNodeList(); // Frontier nodes with unknown cheapest cost
    appendNode(unsettledNodes, source);
    //printf("unsettled nodes: ");
    //printNodeList(unsettledNodes);
    //printf("\n");

    while (!empty_NL(unsettledNodes)) {
        struct Node* currentNode = getCheapestNode(unsettledNodes);
        if (includesNode(unsettledNodes, currentNode)) {
            removeNode(unsettledNodes, currentNode);
        }

        // Iterate through neighbors to find minimum distance and add them to unsettled
        struct EdgeListItem* currentEdgeItem = currentNode->edges->head;
        while (currentEdgeItem) {
            struct Edge* currentEdge = currentEdgeItem->edge;
            //printf("current node data (from dijkstra): %s\n", currentNode->data);
            struct Node* adjacentNode = currentEdge->end;
            if (!includesNode(settledNodes, adjacentNode)) {
                // If it's a shorter path to adjacentNode, update adjacentNode cost and prec
                double newCost = currentNode->cost + currentEdge->weight;
                if (adjacentNode->cost == -1 || newCost < adjacentNode->cost) {
                    updateCost(adjacentNode, newCost);
                    setPrec(adjacentNode, currentNode);
                }
                // Add neighbors to unsettled
                if (!includesNode(unsettledNodes, adjacentNode)) {
                    appendNode(unsettledNodes, adjacentNode);
                }
            }
            currentEdgeItem = currentEdgeItem->next;
        }
        appendNode(settledNodes, currentNode);
    }
    return getShortestPath(source, goal);
}

// TEST!
int main() {
    struct Graph* g = createGraph(10);

    struct Node* nodeA = createNode(g, "A");
    struct Node* nodeB = createNode(g, "B");
    struct Node* nodeC = createNode(g, "C");
    struct Node* nodeD = createNode(g, "D"); 
    struct Node* nodeE = createNode(g, "E");
    struct Node* nodeF = createNode(g, "F");

    addEdge(g, nodeA, nodeB, 10.0);
    addEdge(g, nodeA, nodeC, 15.0);
    addEdge(g, nodeB, nodeD, 12.0);
    addEdge(g, nodeB, nodeF, 15.0);
    addEdge(g, nodeC, nodeE, 10.0);
    addEdge(g, nodeD, nodeE, 2.0);
    addEdge(g, nodeD, nodeF, 1.0);
    addEdge(g, nodeF, nodeE, 5.0);

    //printf("here!\n");

    struct NodeList* path = dijkstra(g, nodeA, nodeF);

    // Print data of each node (start to finish) for testing
    struct NodeListItem* current = path->head;
    while (current) {
        //printNode(current->node);
        current = current->next;
    }

    return length_NL(path);
}