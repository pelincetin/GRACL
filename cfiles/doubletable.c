#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "graph.c"
#endif

struct DoubleTable* createDoubleTable(int predicted_size) {
    struct DoubleTable* dt = malloc(sizeof(struct DoubleTable));
    dt->arr = (DoubleTableItem *)malloc(sizeof(DoubleTableItem)*size);  
    dt->size = size;
    dt->keys = createNodeList();
    if (pthread_mutex_init(&dt->lock, NULL) !=0) {
        fprintf(stderr, "createDoubleTable: Failure to initialize mutex\n");
        exit(1); 
    }
    return dt;
}

int hashCode_dt(struct DoubleTable* dt, struct Node* node) {
    int id_node = node->id;
    return id_node % dt->size;
}

double get(struct DoubleTable* dt, struct Node* n) {
    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start;
    start = dt->arr[hashIndex];
    while (start) {
        if (start->entry && nodeEquals(start->entry->key, n)) {
            return start->entry->dub;
        }
        else {
            start = start->next;
        }
    } 
    exit(1);
}

struct DoubleTableLLItem* createDoubleTable(struct Node* n, double data) {
    struct DoubleTableLLItem* dubtab = malloc(sizeof(DoubleTableLLItem));
    dubtab->key = n;
    dubtab->dub = data;
}

void insert(struct DoubleTable* dt, struct Node* n, double data) {
    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start = dt->hashArray[hashIndex];
    while (start && start->next) {
        start = start->next;
    }
    start->next = createDoubleTableLLItem(n, data);
    appendNode(dt->keys, n);
    return;
}

struct NodeList* keys(struct DoubleTable* dt){
    return dt->keys;
}

bool includes(struct DoubleTable* dt, struct Node* n) {
    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start;
    start = dt->arr[hashIndex];
    while (start) {
        if (start->entry && nodeEquals(start->entry->key, n)) {
            return true
        }
        else {
            start = start->next;
        }
    } 
    return false;
}

int delete(struct DoubleTable* dt, struct Node* n) {
    // remove it from keys
    struct NodeList* all_nodes = malloc(sizeof(struct NodeList));
    all_nodes = keys(dt);
    removeNode(all_nodes, n);

    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start;
    struct DoubleTableItem* start_perm;
    start = dt->arr[hashIndex];
    start_perm = dt->arr[hashIndex];
    while (start) {
        // find node to delete
        if (start->entry && nodeEquals(start->entry->key, n)) {
            if (start->prev == NULL) { // start of list
                dt->arr[hashIndex] = start->next;
                if (start->next) {
                    start->next->prev = NULL;
                }
            }
            else if (start->next == NULL) { // end of list
                start->prev->next = NULL;
            }
            else {
                start->prev->next = start->next;
                start->next->prev = start->prev;
            }
        }
        else {
            start = start->next;
        }
    }
    return 0;
}

