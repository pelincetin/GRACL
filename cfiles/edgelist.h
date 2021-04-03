#include <stdlib.h>
#include <string.h>
#include "edge.h"

// Move to general library eventually
struct EdgeList* createEdgeList() {
    struct EdgeList* edge_list = malloc(sizeof(struct EdgeList));
    edge_list->head = NULL;
    edge_list->tail = NULL;
    return edge_list;
}

struct EdgeListItem* createEdgeListItem(struct Edge* e) {
    struct EdgeListItem* item = malloc(sizeof(struct EdgeListItem));
    item->edge = e;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

struct Edge* removeFirst(struct EdgeList* edge_list) {
    struct EdgeListItem *head;
    head = edge_list->head;
    if (head) {
        edge_list->head = head->next;
        edge_list->head->prev = NULL;
        return head->edge;
    } else { 
        // NEED TO HANDLE THE CASE WHERE HEAD DOESNT EXIST, EMPTY LIST 
       return NULL;
    }
}

struct Edge* removeLast(struct EdgeList* edge_list) {
    if (edge_list->tail) {
        struct EdgeListItem *last = edge_list->tail;
        struct EdgeListItem *prev = last->prev;
        edge_list->tail = prev;
        prev->next = NULL;
        return last->edge;
    } else { 
        // NEED TO HANDLE THE CASE WHERE LAST DOESNT EXIST, EMPTY LIST 
        return NULL;
    }
}

// WHY WAS APPEND ORIGINALLY AN INT TYPE IF PREPEND WAS VOID?
// Changed names since stdio.h has append and prepend
// What about error handling? What if e is null?
void appendEdge(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem* new_last = createEdgeListItem(e);
    if (!empty_EL(edge_list)) {
        // if list not empty;
        new_last->prev = edge_list->tail;
        struct EdgeListItem *old_last = malloc(sizeof(struct EdgeListItem));
        old_last = edge_list->tail;
        old_last->next = new_last;
        edge_list->tail = new_last;
    } else {
        // if list is empty;
        edge_list->head = new_last;
        edge_list->tail = new_last;
    }
    return;
}

void prependEdge(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem *prepend_item = createEdgeListItem(e);
    struct EdgeListItem *head = edge_list->head;
    prepend_item->next = head;
    head->prev = prepend_item;
    edge_list->head = prepend_item;
    if (!head) {
        // if list is empty
        edge_list->head = prepend_item;
        edge_list->tail = prepend_item;
    }
    return; 
}

// Changed name from remove because stdio.h has its own remove
int removeEdge(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem* head = edge_list->head;
    struct EdgeListItem* prev = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    }
    while (head) {
        if (edgeEquals(e, head->edge)) {
            if (prev) {
                prev->next = head->next;
            } else {
                edge_list->head = head->next;
            }
            return 0;
        }
        prev = head;
        head = head->next;
    }
    return -1;
}
