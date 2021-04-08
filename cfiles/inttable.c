#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

struct IntTable* createIntTable(int size){
    struct IntTableItem* d = malloc(sizeof(struct IntTableItem) * size);
    for (int i = 0; i < size; i++) {
        d[i].key = NULL;
        d[i].value = 0;
    }
    struct IntTable* it = malloc(sizeof(struct IntTable));
    it->hashArray = d;
    it->size = size;
    if (pthread_mutex_init(&it->lock, NULL) !=0) {
        fprintf(stderr, "createIntTable: Failure to initialize mutex\n");
        exit(1); 
    } else {
        return it;
    }
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

/*

// DONE WITH OPERATOR
void insert(struct IntTable* it, int key,int data) {
    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
    item->data = data;  
    item->key = key;
    int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        ++hashIndex;
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}

struct IntTableItem* delete(struct IntTableItem* item) {
    int key = item->key;
    int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key) {
            struct DataItem* temp = hashArray[hashIndex];
            hashArray[hashIndex] = dummyItem; // why set it to null instead of dummy item?
            return temp;
        }
        ++hashIndex;
        hashIndex %= SIZE;
    }      
    return NULL;        
}
*/

int main(){
    return 0;
}
