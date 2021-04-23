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
    if(nodeEquals(source, goal)){
        prependNode(path, current);
        return path;
    }
    while (current->precursor) {
        //printf("current%s\n", current->data);
        //printf("precursor%s\n", current->precursor->data);
        prependNode(path, current);
        if(nodeEquals(current, source)){
            //printf("inside if block %s\n", current->data);
            return path;
        }
        current = current->precursor;
        
    }
    return path;
}

// Main Dijkstra method
struct NodeList* dijkstra(struct Graph* g, struct Node* source, struct Node* goal) {
    updateCost(source, 0.0);
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
            //printf("printing current explored node %s\n", currentEdgeItem->edge->end->data);
            struct Edge* currentEdge = currentEdgeItem->edge;
            struct Node* adjacentNode = currentEdge->end;
            if (!includesNode(settledNodes, adjacentNode)) {
                // If it's a shorter path to adjacentNode, update adjacentNode cost and prec
                double newCost = currentNode->cost + currentEdge->weight;
                printf("current node is ");
                printf("%s\n", currentNode->data);
                
                printf("current node cost\n");
                printf("%f\n", cost(currentNode));
                printf("edgeweight");
                printf("%f\n", newCost);
                printf("adjacent node cost");
                printf("%f\n", cost(adjacentNode));

                if (adjacentNode->cost == -1.0 || newCost < adjacentNode->cost) {
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
    //return nothing if goal node is unsettled, i.e. not seen
    //printf("settled\n");
    //printNodeList(settledNodes);
    //printf("\nunsettled\n");
    //printNodeList(unsettledNodes);
    if (!includesNode(settledNodes, goal)){
        //return empty nodelist
        return createNodeList();
    }
    //else return shortest path
    return getShortestPath(source, goal);
}

// Print data of each node (start to finish) for testing
void printPathNodeData(struct NodeList* path){
    //printf("FINAL\n");
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

    printf("Path should be A-B\n");
    printPathNodeData(dijkstra(g, nodeA, nodeB));
    printf("\n");

    printf("Path should not exist\n");
    printPathNodeData(dijkstra(g, nodeF, nodeA));
    printf("\n");

    printf("Path should be D-E\n");
    printPathNodeData(dijkstra(g, nodeD, nodeE));
    printf("\n");

    printf("Path should be B-D-F\n");
    printPathNodeData(dijkstra(g, nodeB, nodeF));
    printf("\n");

    printf("Path should be B-D-E\n");
    printPathNodeData(dijkstra(g, nodeB, nodeE));
    printf("\n");


    printf("Path should be D\n");
    printPathNodeData(dijkstra(g, nodeD, nodeD));
    printf("\n");

    printf("Path should be C\n");
    printPathNodeData(dijkstra(g, nodeC, nodeC));
    printf("\n");

    return 0;
}