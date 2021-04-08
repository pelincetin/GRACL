#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

void incrementId(){
    id_num++;
}

struct IntTable* createIntTable(int size){
    struct IntTableItem* d = malloc(sizeof(struct IntTableItem) * size);
    for (int i = 0; i < size; i++) {
        d[i].key = NULL;
        d[i].value = 0;
    }
    struct IntTable* it = malloc(sizeof(struct IntTable));
    it->hashArray = d;
    it->size = size;
    it->keys = createNodeList();
    if (pthread_mutex_init(&it->lock, NULL) !=0) {
        fprintf(stderr, "createIntTable: Failure to initialize mutex\n");
        exit(1); 
    }
    return it;
}

int hashCode_it(struct IntTable* it, struct Node* node) {
    int id_node = node->id;
    return id_node % it->size;
}

int search(struct IntTable* it, struct Node* n) {
    int hashIndex = hashCode_it(it, n);
    if(it->hashArray[hashIndex].key == n)
        return it->hashArray[hashIndex].value; 
    exit(1);        
}

// DONE WITH OPERATOR
void insert(struct IntTable* it, struct Node* n, int data) {
    int hashIndex = hashCode_it(it, n);
    it->hashArray[hashIndex].key = n;
    it->hashArray[hashIndex].value = data;
    appendNode(it->keys, n);
    incrementId();
    return;
}

struct NodeList* keys(struct IntTable* it){
    return it->keys;
}

bool includes(struct IntTable* it, struct Node* n){
    struct NodeList* nl = malloc(sizeof(struct NodeList));
    nl = keys(it);
    int ret = includesNode(nl, n);
    if (ret){
        return true;
    }
    return false;
}

int delete(struct IntTable* it, struct Node* n) {
    //remove it from keys
    struct NodeList* all_nodes = malloc(sizeof(struct NodeList));
    all_nodes = keys(it);
    removeNode(all_nodes, n);

    if(it->hashArray[hashCode_it(it, n)].key){
        it->hashArray[hashCode_it(it, n)].value = 0;
        it->hashArray[hashCode_it(it, n)].key = NULL;
        return 1;
    }
    return 0;
}

int main(){
    return 0;
}
