#include "inttable.h"

struct IntTable* createIntTable(int predicted_size) {
    if (predicted_size <= 0) {
        fprintf(stderr, "Error: IntTable must have be at least size 1 or larger\n");
        exit(1);
    }
    struct IntTable* it = malloc(sizeof(struct IntTable));
    it->arr = (struct IntTableItem *)calloc(predicted_size, sizeof(struct IntTableItem));
    it->size = predicted_size;
    it->keys = createNodeList();
    it->graph_id = -1;
    if (pthread_mutex_init(&it->lock, NULL) !=0) {
        fprintf(stderr, "createIntTable: Failure to initialize mutex\n");
        exit(1); 
    }
    return it;
}

int hashCode_it(struct IntTable* it, struct Node* n) {
    int id_node = n->id;
    return id_node % it->size;
}

int _getInt(struct IntTable* it, struct Node* n) {
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
void _insertInt(struct IntTable* it, struct Node* n, int data) {
    if ((it->graph_id != -1) && (it->graph_id != n->parent_graph_id)) {
        fprintf(stderr, "_insertInt error: Cannot insert nodes from different graphs into the same IntTable\n");
        exit(1);
    }
    else if (it->graph_id == -1) {
        it->graph_id = n->parent_graph_id;
    }
    int hashIndex = hashCode_it(it, n);
    struct IntTableItem* start = &it->arr[hashIndex];
    if (start == NULL) {
        it->arr[hashIndex] = *createIntTableItem(n, data);
    }
    else {
        while (start && start->next) {
            start = start->next;
        }
        start->next = createIntTableItem(n, data);
    }
    appendNode(it->keys, n);
    return;
}

struct NodeList* intKeys(struct IntTable* it){
    return it->keys;
}

bool inInt(struct IntTable* it, struct Node* n) {
    int hashIndex = hashCode_it(it, n);
    struct IntTableItem* start = &it->arr[hashIndex];
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

int deleteInt(struct IntTable* it, struct Node* n) {
    // remove it from keys
    struct NodeList* all_nodes = malloc(sizeof(struct NodeList));
    all_nodes = intKeys(it);
    removeNode(all_nodes, n);

    int hashIndex = hashCode_it(it, n);
    struct IntTableItem* start;
    struct IntTableItem* prev;
    start = &it->arr[hashIndex];
    prev = NULL;
    while (start) {
        // find node to delete
        if (start->entry && nodeEquals(start->entry->key, n)) {
            if (prev == NULL) { // start of list
                it->arr[hashIndex] = *start->next;
            }
            else if (start->next == NULL) { // end of list
                prev->next = NULL;
            }
            else {
                prev->next = start->next;
            }
            return 0;            
        }
        else {
            prev = start;
            start = start->next;
        }
    }
    return 0;
}