#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Can pass a pointer from a lockednode to a lockedobject safely
// All objects should look like lockednode -- no need for plain node
// Need a cast operation to make llvm types happy
int id_num=1;

struct LockedObject
{
    pthread_mutex_t lock;
};

struct LockedNode
{
    pthread_mutex_t lock;
    int id; // Only used under the hood
    char *data;
    bool visited;
    // struct LockedEdgeList neighbors;
};

// struct LockedEdge
// {
//     pthread_mutex_t lock;
//     double weight; 
//     struct LockedNode start; // Should these be pointers to nodes?
//     struct LockedNode end;
// };

// struct LockedGraph
// {
//     pthread_mutex_t lock;
//     struct LockedNodeList nodes; // Should these be pointers?
//     struct LockedEdgeList edges; 
// };

// struct LockedEdgeList
// {
//     pthread_mutex_t lock;
//     struct LockedEdge edge;
//     struct EdgeListItem *next;
//     struct EdgeListItem *prev;
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