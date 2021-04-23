#include "node.h"

const char* data(struct Node* node)
{
    return node->data;
}

/* Return the edgelist of surrounding edges */
struct EdgeList* edges(struct Node* node)
{
    return node->edges; 
}

/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct Node* node)
{
    return node->visited;
}

struct Node* updateData(struct Node* node, char* new_data)
{
    node->data = new_data;
    return node;
}

/* Updates the visited field on the node to be the inputted bool */
struct Node* updateVisited(struct Node* node, bool tf)
{
    node->visited = tf;
    return node;
}

double cost(struct Node* node)
{
    return node->cost;
}

double incrementCost(struct Node* node)
{
    node->cost = node->cost + 1.0;
    return node->cost;
}

double decrementCost(struct Node* node)
{
    node->cost = node->cost - 1.0;
    return node->cost;
}

double updateCost(struct Node* node, double new_cost)
{
    node->cost = new_cost;
    return node->cost;
}

struct Node* prec(struct Node* node)
{
    return node->precursor;
}

struct Node* setPrec(struct Node* node, struct Node* precursor)
{
    node->precursor = precursor;
    return node;
}

bool nodeEquals(struct Node* node1, struct Node* node2)
{
    return (node1->id == node2->id);
}

struct Edge* getEdge(struct Node* node1, struct Node* node2)
{
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

