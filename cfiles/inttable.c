#include <stdlib.h>
#include <string.h>

struct IntTable
{
    struct DataItem* hashArray[SIZE]; 
    struct DataItem* dummyItem;
    struct DataItem* item;
}

struct DataItem {
    int data;   
    int key;
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
    return key % SIZE;
}

// DONE WITH OPERATOR
struct DataItem *search(int key) {
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

struct DataItem* delete(struct DataItem* item) {
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

//https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm