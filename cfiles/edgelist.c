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
int .prepend(Edge e)
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


int remove(struct EdgeList* edge_list, Edge e) {
    struct EdgeListItem* current = head;
    struct EdgeListItem* previous = NULL;
    if(head == NULL) {
        return -1;
    }
    while(current->edge != e) {
        if(current->next == NULL) {
            return -1;
        } else {
            previous = current;
            current = current->next;             
        }
    }
    if(current == head) {
        head = head->next;
    } else {
        current->prev->next = current->next;
    }    
    if(current == last) {
        last = current->prev;
    } else {
        current->next->prev = current->prev;
    }
    return 0; 
}

// WHY WAS APPEND ORIGINALLY AN INT TYPE IF PREPEND WAS VOID?
// DOESN'T SUPER MAKE SENSE
void append(struct EdgeList* edge_list, Edge* e) {
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

void prepend(struct EdgeList* edge_list, Edge* e) {
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