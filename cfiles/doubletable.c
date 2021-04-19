#include "doubletable.h"

struct DoubleTable* createDoubleTable(int predicted_size) {
    struct DoubleTable* dt = malloc(sizeof(struct DoubleTable));
    dt->arr = (struct DoubleTableItem *)malloc(sizeof(struct DoubleTableItem)*predicted_size);  
    dt->size = predicted_size;
    dt->keys = createNodeList();
    dt->graph_id = -1;
    if (pthread_mutex_init(&dt->lock, NULL) !=0) {
        fprintf(stderr, "createDoubleTable: Failure to initialize mutex\n");
        exit(1); 
    }
    return dt;
}

int hashCode_dt(struct DoubleTable* dt, struct Node* n) {
    int id_node = n->id;
    return id_node % dt->size;
}

double _getDouble(struct DoubleTable* dt, struct Node* n) {
    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start;
    start = &dt->arr[hashIndex];
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

struct DoubleTableLLItem* createDoubleTableLLItem(struct Node* n, double data) {
    struct DoubleTableLLItem* dubtab = malloc(sizeof(struct DoubleTableLLItem));
    dubtab->key = n;
    dubtab->dub = data;
    return dubtab;
}

struct DoubleTableItem* createDoubleTableItem(struct Node* n, double data) {
    struct DoubleTableItem* dubtab = malloc(sizeof(struct DoubleTableItem));
    dubtab->entry = createDoubleTableLLItem(n, data);
    dubtab->next = NULL;
    return dubtab;
}

// technically complexity could improve if we insert in a sorted manner
// TODO
void _insertDouble(struct DoubleTable* dt, struct Node* n, double data) {
    if ((dt->graph_id != -1) && (dt->graph_id != n->parent_graph_id)) {
        fprintf(stderr, "_insertDouble error: Cannot insert nodes from different graphs into the same DoubleTable\n");
    }
    else if (dt->graph_id == -1) {
        dt->graph_id = n->parent_graph_id;
    }
    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start = &dt->arr[hashIndex];
    if (start == NULL) {
        dt->arr[hashIndex] = *createDoubleTableItem(n, data);
    }
    else {
        while (start && start->next) {
            start = start->next;
        }
        start->next = createDoubleTableItem(n, data);
    }
    appendNode(dt->keys, n);
    return;
}

struct NodeList* doubleKeys(struct DoubleTable* dt){
    return dt->keys;
}

bool inDouble(struct DoubleTable* dt, struct Node* n) {
    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start;
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

int deleteDouble(struct DoubleTable* dt, struct Node* n) {
    // remove it from keys
    struct NodeList* all_nodes = malloc(sizeof(struct NodeList));
    all_nodes = doubleKeys(dt);
    removeNode(all_nodes, n);

    int hashIndex = hashCode_dt(dt, n);
    struct DoubleTableItem* start;
    struct DoubleTableItem* prev;
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
            return 0;
        }
        else {
            prev = start;
            start = start->next;
        }
    }
    return 0;
}

