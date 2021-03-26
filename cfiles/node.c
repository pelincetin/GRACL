#include <stdlib.h>
#include <stdio.h>
#include "lockedobject.h"
#include <pthread.h>

void incrementId(){
    id_num++;
}

struct LockedNode* createNode(char* data){
    struct LockedNode* node = malloc(sizeof(struct LockedNode));
    node->data = data;
    node->visited = false;
    node->id = id_num;
    incrementId();
    if (pthread_mutex_init(node->lock, NULL) {
        print("createNode: Failure to initialize mutex")
        // TODO: ERROR HANDLING HERE 
        node->id = -1
        return node;
    }
    else {
        return node;
    }
};

const char* data(struct LockedNode* node)
{
    return node->data;
}

/*
NodeList neighbors()
{

    return neighbors;
}
*/

/* Returns a boolean representing
 * if the node has already been visited. */
bool visited(struct LockedNode* node)
{
    return node->visited;
}

int updateData(char* new_data, struct LockedNode* node)
{
    node->data = new_data;
    return node;
}

/* Updates the visited field on the Node to be the new bool passed in */
int updateVisited(bool tf, struct LockedNode* node)
{
    node->visited = tf;
    return node;
}

/* Compares the two Node objects by id 
 * Returns True if they are the same and returns False if not */
bool equals(struct LockedNode* node1, struct LockedNode* node2)
{
    if (node1->id == node2->id) {
        return true;
    }
    return false;
}