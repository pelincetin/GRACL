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
    if (pthread_mutex_init(&dt->lock, NULL) !=0) {
        fprintf(stderr, "createDoubleTable: Failure to initialize mutex\n");
        exit(1); 
    } else {
        return dt;
    }
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
    incrementId();
    return;
}

/*
struct DoubleTableItem* delete(struct DoubleTable* dt, struct DataItem* item) {
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
