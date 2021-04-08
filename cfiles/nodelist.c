#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "lockedobject.h"
#include "node.c"
#endif

struct NodeListItem* createNodeListItem(struct Node* e) {
    struct NodeListItem* item = malloc(sizeof(struct NodeListItem));
    item->node = e;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

struct NodeList* createNodeList() {
    struct NodeList* node_list = malloc(sizeof(struct NodeList));
    node_list->head = NULL;
    node_list->tail = NULL;
    return node_list;
}

struct Node* removeFirst_NL(struct NodeList* node_list) {
    struct NodeListItem* head;
    head = node_list->head;
    if (head) {
        node_list->head = head->next;
        node_list->head->prev = NULL;
        return head->node;
    } else { 
        return NULL; 
    }
}

struct Node* removeLast_NL(struct NodeList* node_list) {
    struct NodeListItem* last = node_list->tail;
    struct NodeListItem* prev = NULL;
    if (last) {
        prev = last->prev;
        node_list->tail = prev;
        if (prev) {
            prev->next = NULL;
        }
        return last->node;
    } else { 
        return NULL;
    }
} 

void prependNode(struct NodeList* node_list, struct Node* e) {
    struct NodeListItem* prepend_item = createNodeListItem(e);
    struct NodeListItem* head = node_list->head;
    prepend_item->next = head;
    head->prev = prepend_item;
    node_list->head = prepend_item;
    if (!head) {
        // if list is empty
        node_list->tail = prepend_item;
    }
    return; 
}


bool empty_NL(struct NodeList* node_list) {
    struct NodeListItem* current;
    current = node_list->head;
    return (current == NULL);
}

int length_NL(struct NodeList* node_list) {
    int length = 0;
    struct NodeListItem *current;
    current = node_list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void appendNode(struct NodeList* node_list, struct Node* n) {
    struct NodeListItem* new_last = createNodeListItem(n);
    if (!empty_NL(node_list)) {
        // if list not empty;
        new_last->prev = node_list->tail;
        struct NodeListItem* old_last = malloc(sizeof(struct NodeListItem));
        old_last = node_list->tail;
        old_last->next = new_last;
        node_list->tail = new_last;
    } else {
        // if list is empty;
        node_list->head = new_last;
        node_list->tail = new_last;
    }
    return;
}





int removeNode(struct NodeList* node_list, struct Node* e) {
    struct NodeListItem* head = node_list->head;
    struct NodeListItem* prev = NULL;
    struct NodeListItem* next = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    } else {
        prev = head->prev;
        while (head) {
            if (nodeEquals(e, head->node)) {
                if (prev) {
                    next = head->next;
                    prev->next = next;
                    if (next) {
                        next->prev = prev;
                    }
                } else {
                    next = head->next;
                    node_list->head = next;
                    if (next) {
                        next->prev = NULL;
                    }
                }
                return 0;
            }
            prev = head;
            head = head->next;
        }
        return -1;
    }
} 

bool includesNode(struct NodeList* nl, struct Node* n){
    struct NodeListItem* temp = malloc(sizeof(struct NodeListItem));
    if (nl != NULL){
        temp = nl->head;
    } else {
        return false;
    }
    while (temp) {
        if (n->id == temp->node->id){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

struct NodeList* neighbors(struct Node* node){
    struct EdgeList* edges = node->edges;
    struct NodeList* neighbors = createNodeList();
    struct EdgeListItem* current = edges->head;
    while (current != NULL) {
        appendNode(neighbors, current->edge->end);
        current = current->next;
    }
    return neighbors; 
}
