#include <stdlib.h>
#include <string.h>
#include "commonFunctions.h"

// Move to general library eventually
struct NodeList* createNodeList() {
    struct NodeList* node_list = malloc(sizeof(struct NodeList));
    node_list->head = NULL;
    node_list->tail = NULL;
    return node_list;
}

struct Node* removeFirst(struct NodeList* node_list) {
    struct NodeListItem *head;
    head = node_list->head;
    if (head) {
        node_list->head = head->next;
        node_list->head->prev = NULL;
        return head->node;
    } else { 
        exit(1); 
    }
}

struct Node* removeLast(struct NodeList* node_list) {
    if (node_list->tail) {
        struct NodeListItem *last = node_list->tail;
        struct NodeListItem *prev = last->prev;
        node_list->tail = prev;
        prev->next = NULL;
        return last->node;
    } else { 
        // NEED TO HANDLE THE CASE WHERE LAST DOESNT EXIST, EMPTY LIST 
        exit(1); // ?
    }
}

// Changed name from remove because stdio.h has its own remove
int removeNode(struct NodeList* node_list, struct Node* e) {
    struct NodeListItem* head = node_list->head;
    struct NodeListItem* prev = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    }
    while (head) {
        if (nodeEquals(e, head->node)) {
            if (prev) {
                prev->next = head->next;
            } else {
                node_list->head = head->next;
            }
            return 0;
        }
        prev = head;
        head = head->next;
    }
    return -1;
}

void prependNode(struct NodeList* node_list, struct Node* e) {
    struct NodeListItem *prepend_item = createNodeListItem(e);
    struct NodeListItem *head = node_list->head;
    prepend_item->next = head;
    head->prev = prepend_item;
    node_list->head = prepend_item;
    if (!head) {
        // if list is empty
        node_list->tail = prepend_item;
    }
    return; 
}
