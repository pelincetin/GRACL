#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>


/* Can pass a pointer from a lockednode to a lockedobject safely
 * All objects should look like lockednode -- no need for plain node
 * Need a cast operation to make llvm types happy */
int id_num = 1;
int SIZE = 500;

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

struct EdgeListItem {
    struct Edge* edge;
    struct EdgeListItem* next;
    struct EdgeListItem* prev;
};

struct EdgeList {
    struct EdgeListItem* head;
    struct EdgeListItem* tail;
};

struct NodeListItem {
    struct Node* node;
    struct NodeListItem* next;
    struct NodeListItem* prev;
};

struct NodeList {
    struct NodeListItem* head;
    struct NodeListItem* tail;
};

struct DataItem {
    struct Node* key;
    struct NodeList* value;
};

struct Graph
{
    struct DataItem* hashArray; 
    struct NodeList* nodes;
    int size;
};

struct IntTableItem {
    struct Node* key;
    int* value;
};

struct DoubleTableItem {
    struct Node* key;
    double* value;
};

struct IntTable
{
    pthread_mutex_t lock;
    struct IntTableItem* hashArray; 
    int size;
};

struct DoubleTable
{
    pthread_mutex_t lock;
    struct DoubleTableItem* hashArray; 
    int size;
};
