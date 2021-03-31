#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

/* Can pass a pointer from a lockednode to a lockedobject safely
 * All objects should look like lockednode -- no need for plain node
 * Need a cast operation to make llvm types happy */
int id_num=1;

struct Object {
    pthread_mutex_t lock;
};

struct Node {
    pthread_mutex_t lock;
    int id; // Only used under the hood
    char *data;
    bool visited;
    struct EdgeList* edges;
};

struct Edge {
    // Edwards OH: you can have a tail pointer and the idea would be that
    // the edge always knows what its siblings are and get rid 
    // of edgelists alltogether
    // go further and remove struct Node* start;  if you have an agreement that
    // the tail pointer off of edge just points to the edge on that node
    pthread_mutex_t lock;
    double weight; 
    struct Node* start; 
    struct Node* end;
};

struct EdgeList {
    struct EdgeListItem *head;
    struct EdgeListItem *tail;
};

struct NodeList {
    struct NodeListItem *head;
    struct NodeListItem *tail;
};

// struct Graph
// {
//     pthread_mutex_t lock;
//     struct NodeList nodes; // Should these be pointers?
//     struct EdgeList edges; 
// };

// struct DoubleTable
// {
//     pthread_mutex_t lock;
//     struct DataItem* hashArray[SIZE]; 
//     struct DataItem* dummyItem;
//     struct DataItem* item;
// };

// struct IntTable
// {
//     pthread_mutex_t lock;
//     struct DataItem* hashArray[SIZE]; 
//     struct DataItem* dummyItem;
//     struct DataItem* item;
// };
