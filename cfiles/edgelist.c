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
    last = edge_list->last;
    if (last) {
        prev = last->prev;
        edge_list->last = prev;
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

int append(struct EdgeList* edge_list, Edge* e) {
    struct EdgeListItem *last_item;
    last_item = malloc(sizeof(struct EdgeListItem));
    last_item->edge = e; 
    last_item->next = NULL;
    last_item->prev = edge_list->last;
    if (edge_list->head) {
        // if list not empty; 
        edge_list->last->next = last_item;
    } else {
        // if list is empty;
        edge_list->head = last_item;
        edge_list->last = last_item;
    }
}

void prepend(struct EdgeList* edge_list, Edge e) {
    struct EdgeListItem *link = (struct EdgeListItem*) malloc(sizeof(struct EdgeListItem));
    link->edge = e;
    if(empty()) {
        last = link;
    } else {
        head->prev = link;
    }
    link->next = head;
    head = link;
    if (head->edge == e) {
        return 0;
    }
    return -1;
}
*/
// https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_program_in_c.htm