#include <stdlib.h>
#include <string.h>

struct EdgeListItem {
    struct Edge edge;
    struct EdgeListItem *next;
    struct EdgeListItem *prev;
};

// SHOULD THIS BE IN THIS FILE WITH ALL OF THE FUNCTIONS?
struct EdgeList
{
    struct EdgeListItem *head = NULL;
    struct EdgeListItem *last = NULL;
    /* Mutex?? */
};

/*
int length() {
    int length = 0;
    struct EdgeListItem *current;
    for(current = head; current != NULL; current = current->next){
        length++;
    }
    return length;
}

bool empty() {
    return head == NULL;
}

struct EdgeListItem* removeFirst() {
    struct EdgeListItem *tempLink = head;
    if(head->next == NULL){
        last = NULL;
    } else {
        head->next->prev = NULL;
    }
    head = head->next;
    return tempLink; // LRM says actual edge, but this is a pointer
}

struct EdgeListItem* removeLast() {
    struct EdgeListItem *tempLink = last;
    if(head->next == NULL) {
        head = NULL;
    } else {
        last->prev->next = NULL;
    }
    last = last->prev;
    return tempLink; // LRM says actual edge, but this is a pointer
}

int remove(Edge e) {
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

int append(Edge e) {
    struct EdgeListItem *link = (struct EdgeListItem*) malloc(sizeof(struct EdgeListItem));
    link->edge = e; // Should this be a pointer to the edge?
    if(empty()) {
        last = link;
    } else {
        last->next = link;
        link->prev = last;
    }
    last = link;
    if (last->edge == e) {
        return 0;
    }
    return -1;
}

void prepend(Edge e) {
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