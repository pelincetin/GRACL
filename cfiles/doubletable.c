#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

int hashCode_dt(struct DoubleTable* dt, struct Node* node) {
    int id_node = node->id;
    return id_node % dt->size;
}

/*
// DONE WITH OPERATOR
struct DataItem* search(int key) {
    int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key)
            return hashArray[hashIndex]; 
        ++hashIndex;
        hashIndex %= SIZE;
    }
    return NULL;        
}

// DONE WITH OPERATOR
void insert(int key,int data) {
    struct DoubleTableItem* item = (struct DoubleTableItem*) malloc(sizeof(struct DoubleTableItem));
    item->data = data;  
    item->key = key;
    int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        ++hashIndex;
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}

struct DoubleTableItem* delete(struct DataItem* item) {
    int key = item->key;
    int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key) {
            struct DoubleTableItem* temp = hashArray[hashIndex];
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
