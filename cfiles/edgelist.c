#include <stdlib.h>
#include <string.h>

struct EdgeListItem {
    struct Edge edge;
    struct EdgeListItem *next;
    struct EdgeListItem *prev;
};

/*
int .remove(Edge e)
Edge .removeFirst()
Edge .removeLast()
int .append(Edge e)
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

// GOING TO KEEP WORKING HERE, THIS STILL NEEDS WORK
struct EdgeListItem* removeFirst(struct EdgeList* edge_list) {
    struct EdgeListItem *head;
    head = edge_list->head;
    if (head) {
        if (head->next) {

        } else {
            
        }
    } else { 
        // NEED TO HANDLE THE CASE WHERE HEAD DOESNT EXIST, EMPTY LIST 
    }
}

struct EdgeListItem* removeLast(struct EdgeList* edge_list) {
    struct EdgeListItem *tempLink = last;
    if(head->next == NULL) {
        head = NULL;
    } else {
        last->prev->next = NULL;
    }
    last = last->prev;
    return tempLink; // LRM says actual edge, but this is a pointer
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

int append(struct EdgeList* edge_list, Edge e) {
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