#include <stdlib.h>
#include <string.h>

struct EdgeListItem {
    struct Edge* edge;
    struct EdgeListItem* next;
    struct EdgeListItem* prev;
};

/*
STILL NEED IMPLEMENTATION: 
int .remove(Edge e)
*/

int length(struct EdgeList* edge_list) {
    int length = 0;
    struct EdgeListItem *current;
    current = edge_list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

bool empty(struct EdgeList* edge_list) {
    struct EdgeListItem *current;
    current = edge_list->head;
    return (current == NULL) 
}

struct Edge* removeFirst(struct EdgeList* edge_list) {
    struct EdgeListItem *head;
    head = edge_list->head;
    if (head) {
        edge_list->head = head->next;
        edge_list->head->prev = NULL;
        return *(head->edge);
    } else { 
        // NEED TO HANDLE THE CASE WHERE HEAD DOESNT EXIST, EMPTY LIST 
        exit(1) // ?
    }
}

struct Edge* removeLast(struct EdgeList* edge_list) {
    struct EdgeListItem *last;
    last = edge_list->tail;
    if (last) {
        prev = last->prev;
        edge_list->tail = prev;
        prev->next = NULL;
        return *(last->edge);
    } else { 
        // NEED TO HANDLE THE CASE WHERE LAST DOESNT EXIST, EMPTY LIST 
        exit(1) // ?
    }
}

int remove(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem* head = edge_list->head;
    struct EdgeListItem* prev = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    }
    while (head) {
        if (edge_equals(e, head->edge)) {
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

/*
 * This should be moved to edge @ defne and hadley */ 

bool edge_equals(struct Edge* e1, struct Edge* e2) {
    return (((e1->weight == e2->weight) && equals(e1->start, e2->start))
     && equals(e1->end, e2->end))
}


// WHY WAS APPEND ORIGINALLY AN INT TYPE IF PREPEND WAS VOID?
void append(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem *append_item;
    last_item = malloc(sizeof(struct EdgeListItem));
    append_item->edge = e; 
    append_item->next = NULL;
    append_item->prev = edge_list->tail;
    if (edge_list->head) {
        // if list not empty; 
        edge_list->tail->next = append_item;
    } else {
        // if list is empty;
        edge_list->head = append_item;
        edge_list->tail = append_item;
    }
    return;
}

void prepend(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem *prepend_item;
    prepend_item = malloc(sizeof(struct EdgeListItem));
    prepend_item->edge = e;
    prepend_item->prev = NULL;
    head = edge_list->head
    prepend_item->next = head;
    edge_list->head = prepend_item;
    if (!head) {
        // if list is empty
        edge_list->tail = prepend_item;
    }
    return; 
}
*/
// https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_program_in_c.htm