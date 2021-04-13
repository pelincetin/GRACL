#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

void incrementId(){
    id_num++;
}

struct DoubleTable* createDoubleTable(int size){
    struct DoubleTableItem* d = malloc(sizeof(struct DoubleTableItem) * size);
    for (int i = 0; i < size; i++) {
        d[i].key = NULL;
        d[i].value = 0.0;
    }
    struct DoubleTable* dt = malloc(sizeof(struct DoubleTable));
    dt->hashArray = d;
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

// DONE WITH OPERATOR
double search(struct DoubleTable* dt, struct Node* n) {
    int hashIndex = hashCode_dt(dt, n);
    if(dt->hashArray[hashIndex].key == n)
        return dt->hashArray[hashIndex].value; 
    exit(1);      
}

// DONE WITH OPERATOR
void insert(struct DoubleTable* dt, struct Node* n, double data) {
    int hashIndex = hashCode_dt(dt, n);
    dt->hashArray[hashIndex].key = n;
    dt->hashArray[hashIndex].value = data;
    appendNode(dt->keys, n);
    incrementId();
    return;
}

struct NodeList* keys(struct DoubleTable* dt){
    return dt->keys;
}

bool includes(struct DoubleTable* dt, struct Node* n){
    struct NodeList* nl = malloc(sizeof(struct NodeList));
    nl = keys(dt);
    int ret = includesNode(nl, n);
    if (ret){
        return true;
    }
    return false;
}

int delete(struct DoubleTable* dt, struct Node* n) {
    //remove it from keys
    struct NodeList* all_nodes = malloc(sizeof(struct NodeList));
    all_nodes = keys(dt);
    removeNode(all_nodes, n);

    if(dt->hashArray[hashCode_dt(dt, n)].key){
        dt->hashArray[hashCode_dt(dt, n)].value = 0.0;
        dt->hashArray[hashCode_dt(dt, n)].key = NULL;
        return 1;
    }
    return 0;
}

/*
int main(){
    return 0;
}
*/