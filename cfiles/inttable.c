#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "graph.c"
#endif

struct IntTable* createIntTable(int predicted_size) {
    struct IntTable* it = malloc(sizeof(struct IntTable));
    it->arr = (struct IntTableItem *)malloc(sizeof(struct IntTableItem)*predicted_size);  
    it->size = predicted_size;
    it->keys = createNodeList();
    if (pthread_mutex_init(&dt->lock, NULL) !=0) {
        fprintf(stderr, "createIntTable: Failure to initialize mutex\n");
        exit(1); 
    }
    return it;
}

int hashCode_it(struct IntTable* it, struct Node* node) {
    int id_node = node->id;
    return id_node % it->size;
}

int get(struct IntTable* it, struct Node* n) {
    int hashIndex = hashCode_it(it, n);
    struct IntTableItem* start;
    start = &it->arr[hashIndex];
    while (start) {
        if (start->entry && nodeEquals(start->entry->key, n)) {
            return start->entry->value;
        }
        else {
            start = start->next;
        }
    } 
    exit(1);
}

struct IntTableLLItem* createIntTableLLItem(struct Node* n, int data) {
    struct IntTableLLItem* inttab = malloc(sizeof(struct IntTableLLItem));
    inttab->key = n;
    inttab->value = data;
    return inttab;
}

struct IntTableItem* createIntTableItem(struct Node* n, int data) {
    struct IntTableItem* inttab = malloc(sizeof(struct IntTableItem));
    inttab->entry = createIntTableLLItem(n, data);
    inttab->next = NULL;
    return inttab;
}

// technically complexity could improve if we insert in a sorted manner
// TODO
void insert(struct IntTable* dt, struct Node* n, int data) {
    int hashIndex = hashCode_dt(dt, n);
    struct IntTableItem* start = &dt->arr[hashIndex];
    if (start == NULL) {
        dt->arr[hashIndex] = *createIntTableItem(n, data);
    }
    else {
        while (start && start->next) {
            start = start->next;
        }
        start->next = createIntTableItem(n, data);
    }
    appendNode(dt->keys, n);
    return;
}

struct NodeList* keys(struct IntTable* dt){
    return dt->keys;
}

bool includes(struct IntTable* dt, struct Node* n) {
    int hashIndex = hashCode_dt(dt, n);
    struct IntTableItem* start;
    start = &dt->arr[hashIndex];
    while (start) {
        if (start->entry && nodeEquals(start->entry->key, n)) {
            return true;
        }
        else {
            start = start->next;
        }
    } 
    return false;
}

int delete(struct IntTable* dt, struct Node* n) {
    // remove it from keys
    struct NodeList* all_nodes = malloc(sizeof(struct NodeList));
    all_nodes = keys(dt);
    removeNode(all_nodes, n);

    int hashIndex = hashCode_dt(dt, n);
    struct IntTableItem* start;
    struct IntTableItem* prev;
    start = &dt->arr[hashIndex];
    prev = NULL;
    while (start) {
        // find node to delete
        if (start->entry && nodeEquals(start->entry->key, n)) {
            if (prev == NULL) { // start of list
                dt->arr[hashIndex] = *start->next;
            }
            else if (start->next == NULL) { // end of list
                prev->next = NULL;
            }
            else {
                prev->next = start->next;
            }
        }
        else {
            prev = start;
            start = start->next;
        }
    }
    return 0;
}