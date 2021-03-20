#include <stdlib.h>
#include <string.h>

struct NodeListItem {
    struct Node node;
    struct NodeListItem *next;
    struct NodeListItem *prev;
};

// SHOULD THIS BE IN THIS FILE WITH ALL OF THE FUNCTIONS?
struct NodeList
{
    struct NodeListItem *head = NULL;
    struct NodeListItem *last = NULL;
    /* Mutex?? */
};

/*
int length() {
    int length = 0;
    struct NodeListItem *current;
    for(current = head; current != NULL; current = current->next){
        length++;
    }
    return length;
}

bool empty() {
    return head == NULL;
}

struct NodeListItem* removeFirst() {
    struct NodeListItem *tempLink = head;
    if(head->next == NULL){
        last = NULL;
    } else {
        head->next->prev = NULL;
    }
    head = head->next;
    return tempLink; // LRM says actual Node, but this is a pointer
}

struct NodeListItem* removeLast() {
    struct NodeListItem *tempLink = last;
    if(head->next == NULL) {
        head = NULL;
    } else {
        last->prev->next = NULL;
    }
    last = last->prev;
    return tempLink; // LRM says actual Node, but this is a pointer
}

int remove(Node e) {
    struct NodeListItem* current = head;
    struct NodeListItem* previous = NULL;
    if(head == NULL) {
        return -1;
    }
    while(current->Node != e) {
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

int append(Node e) {
    struct NodeListItem *link = (struct NodeListItem*) malloc(sizeof(struct NodeListItem));
    link->node = e; // Should this be a pointer to the Node?
    if(empty()) {
        last = link;
    } else {
        last->next = link;
        link->prev = last;
    }
    last = link;
    if (last->node == e) {
        return 0;
    }
    return -1;
}

void prepend(Node e) {
    struct NodeListItem *link = (struct NodeListItem*) malloc(sizeof(struct NodeListItem));
    link->node = e;
    if(empty()) {
        last = link;
    } else {
        head->prev = link;
    }
    link->next = head;
    head = link;
    if (head->node == e) {
        return 0;
    }
    return -1;
}
*/
// https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_program_in_c.htm