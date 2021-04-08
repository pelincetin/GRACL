#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

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

/*
int main(){
    return 0;
}
*/
