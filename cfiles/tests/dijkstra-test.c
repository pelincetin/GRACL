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
        if (current->node->cost < cheapestCost) {
            cheapestCost = current->node->cost;
            cheapestNode = current->node;
        }
        current = current->next;
    }
    return cheapestNode;
}

// Recurse through goal node's precursors to start node to get full path
struct NodeList* getShortestPath(struct Node* source, struct Node* goal) {
    struct NodeList* path = createNodeList();
    struct Node* current = goal;
    while (current->precursor) {
        prependNode(path, current);
        current = current->precursor;
    }
    return path;
}

// Main Dijkstra method
struct NodeList* dijkstra(struct Graph* g, struct Node* source, struct Node* goal) {
    updateCost(source, 0);
    struct NodeList* settledNodes = createNodeList(); // Nodes with known cheapest cost
    struct NodeList* unsettledNodes = createNodeList(); // Frontier nodes with unknown cheapest cost
    appendNode(unsettledNodes, source);
    while (!empty_NL(unsettledNodes)) {
        struct Node* currentNode = getCheapestNode(unsettledNodes);
        if (includesNode(unsettledNodes, currentNode)) {
            removeNode(unsettledNodes, currentNode);
        }
        // Iterate through neighbors to find minimum distance and add them to unsettled
        struct EdgeListItem* currentEdgeItem = currentNode->edges->head;
        while (currentEdgeItem) {
            struct Edge* currentEdge = currentEdgeItem->edge;
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

// Print data of each node (start to finish) for testing
void printPathNodeData(struct NodeList* path){
    struct NodeListItem* current = path->head;
    while (current) {
        printf("%s ", current->node->data);
        current = current->next;
    }
    printf("\n");
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

    printf("Path should be A-B-D-F\n");
    printPathNodeData(dijkstra(g, nodeA, nodeF));
    printf("\n");

    printf("Path should be A-B-D-E\n");
    printPathNodeData(dijkstra(g, nodeA, nodeE));
    printf("\n");

    printf("Path should be E\n");
    printPathNodeData(dijkstra(g, nodeE, nodeE));
    printf("\n");

    printf("Path should not exist\n");
    printPathNodeData(dijkstra(g, nodeB, nodeC));
    printf("\n");

    return 0;
}