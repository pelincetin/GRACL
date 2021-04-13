#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

int graph_id = 1;
    
struct Node {
    pthread_mutex_t lock;
    int id; // Only used under the hood
    char *data;
    bool visited;
    struct EdgeList* edges;
    struct Node* precursor;
    int cost; 
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
    struct EdgeList* value;
};

struct Graph
{
    struct DataItem* hashArray; 
    struct NodeList* nodes;
    int size;
    int id_num;
    int graph_id_local;
};

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
