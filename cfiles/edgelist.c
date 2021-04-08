#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "commonFunctions.h"
#endif

struct Edge* head_EL(struct EdgeList* edge_list) {
    if (edge_list == NULL) {
        fprintf(stderr, "null EL");
    }
    if (edge_list->head == NULL) {
        fprintf(stderr, "null edge");
    }
    return edge_list->head->edge;
}

struct Edge* tail_EL(struct EdgeList* edge_list) {
    return edge_list->tail->edge;
}

struct Edge* removeFirst_EL(struct EdgeList* edge_list) {
    struct EdgeListItem *head;
    head = edge_list->head;
    if (head) {
        edge_list->head = head->next;
        edge_list->head->prev = NULL;
        return head->edge;
    } else { 
        return NULL;
    }
}

struct Edge* removeLast_EL(struct EdgeList* edge_list) {
    struct EdgeListItem *last = edge_list->tail;
    struct EdgeListItem *prev = NULL;
    if (last) {
        prev = last->prev;
        edge_list->tail = prev;
        if (prev) {
            prev->next = NULL;
        }
        return last->edge;
    } else { 
        return NULL;
    }
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

/*
int main(){
    return 0;
}
*/