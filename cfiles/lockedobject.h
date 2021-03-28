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
    pthread_mutex_t lock;
    double weight; 
    struct Node* start; 
    struct Node* end;
};

struct EdgeList {
    pthread_mutex_t lock; 
    struct EdgeListItem *head;
    struct EdgeListItem *last;
};



// struct LockedGraph
// {
//     pthread_mutex_t lock;
//     struct LockedNodeList nodes; // Should these be pointers?
//     struct LockedEdgeList edges; 
// };


// struct LockedNodeList
// {
//     pthread_mutex_t lock;
//     struct LockedNode node;
//     struct NodeListItem *next;
//     struct NodeListItem *prev;
// };

// struct LockedDoubleTable
// {
//     pthread_mutex_t lock;
//     struct DataItem* hashArray[SIZE]; 
//     struct DataItem* dummyItem;
//     struct DataItem* item;
// };

// struct LockedIntTable
// {
//     pthread_mutex_t lock;
//     struct DataItem* hashArray[SIZE]; 
//     struct DataItem* dummyItem;
//     struct DataItem* item;
// };