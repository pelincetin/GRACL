#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include "edgelist.c"
#include "lockedobject.h"

void incrementId(){
    id_num++;
}

Node createNode(char *data){
    struct LockedNode *Node = malloc(sizeof(struct LockedNode));
    Node.data = data;
    Node.visited = false;
    Node.id = id_num;
    incrementId();
    return Node;
}

const char * data()
{
    // Returns data stored in the Node object.
    return data;
}

NodeList neighbors()
{
    // Returns a list of neighbor Nodes. 
    return neighbors;
}

bool visited()
{
    // Returns a boolean representing if the Node has already been visited.
    return visited;
}



int updateData(String newData)
{
    // Updates the data field on the Node to be the new data passed in and returns 0 on success. On failure, returns -1.
    data = newData;
    if (data != newData) {
        return -1;
    }
    return 0;
}

int updateVisited(bool tf)
{
    // Updates the visited field on the Node to be the new bool passed in and returns 0 on success. On failure, returns -1.
    visited = tf;
    if (visited != tf) {
        return -1;
    }
    return 0;
}

bool equals(Node n)
{
    // Compares the two Node objects. Returns True if they are the same and returns False if they’re not the same.
    // Under the hood, this is implemented by comparing the implicit id associated with the Node object. 
    if (id == n.id) {
        return true;
    }
    return false;
}