#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

int hashCode_it(struct IntTable* it, struct Node* node) {
    int id_node = node->id;
    return id_node % it->size;
}

/*

// DONE WITH OPERATOR
struct IntTableItem* search(struct IntTable* it, int key) {
    int hashIndex = hashCode_it(it, key);
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key)
            return hashArray[hashIndex]; 
        ++hashIndex;
        hashIndex %= SIZE;
    }
    return NULL;        
}

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
