#include "node.h"

const char* data(struct Node* node)
{
    if (node->deleted) {
        fprintf(stderr, "data: Node deleted\n");
        exit(1);
    }
    return node->data;
}

/* Return the edgelist of surrounding edges */
struct EdgeList* edges(struct Node* node)
{
    if (node->deleted) {
        fprintf(stderr, "edges: Node deleted\n");
        exit(1);
    }
    return node->edges; 
}

/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct Node* node)
{
    if (node->deleted) {
        fprintf(stderr, "visited: Node deleted\n");
        exit(1);
    }
    return node->visited;
}

struct Node* updateData(struct Node* node, char* new_data)
{
    if (node->deleted) {
        fprintf(stderr, "updateData: Node deleted\n");
        exit(1);
    }
    node->data = new_data;
    return node;
}

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(struct Node* node, bool tf)
{
    if (node->deleted) {
        fprintf(stderr, "updateVisited: Node deleted\n");
        exit(1);
    }
    node->visited = tf;
    return node;
}

double cost(struct Node* node)
{
    if (node->deleted) {
        fprintf(stderr, "cost: Node deleted\n");
        exit(1);
    }
    return node->cost;
}

double incrementCost(struct Node* node)
{
    if (node->deleted) {
        fprintf(stderr, "incrementCost: Node deleted\n");
        exit(1);
    }
    node->cost = node->cost + 1.0;
    return node->cost;
}

double decrementCost(struct Node* node)
{
    if (node->deleted) {
        fprintf(stderr, "decrementCost: Node deleted\n");
        exit(1);
    }
    node->cost = node->cost - 1.0;
    return node->cost;
}

double updateCost(struct Node* node, double new_cost)
{
    if (node->deleted) {
        fprintf(stderr, "updateCost: Node deleted\n");
        exit(1);
    }
    node->cost = new_cost;
    return node->cost;
}

struct Node* prec(struct Node* node)
{
    if (node->deleted) {
        fprintf(stderr, "prec: Node deleted\n");
        exit(1);
    }
    return node->precursor;
}

struct Node* setPrec(struct Node* node, struct Node* precursor)
{
    if ((node->deleted) || (precursor->deleted)) {
        fprintf(stderr, "setPrec: Node deleted\n");
        exit(1);
    }    
    node->precursor = precursor;
    return node;
}

bool nodeEquals(struct Node* node1, struct Node* node2)
{
    if ((node1->deleted) || (node2->deleted)) {
        fprintf(stderr, "nodeEquals: Node deleted\n");
        exit(1);
    }    
    return (node1->id == node2->id);
}

struct Edge* getEdge(struct Node* node1, struct Node* node2)
{
    if ((node1->deleted) || (node2->deleted)) {
        fprintf(stderr, "getEdge: Node deleted\n");
        exit(1);
    }    
    struct EdgeListItem *current;
    current = node1->edges->head;
    while (current != NULL) {
        struct Node* s_node = current->edge->start;
        struct Node* e_node = current->edge->end;
        if (nodeEquals(s_node, node1) && nodeEquals(e_node, node2)) {
            return current->edge;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

