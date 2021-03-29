#include <stdlib.h>
#include <string.h>
#include "node.h"

struct NodeListItem {
    struct Node* node;
    struct NodeListItem* next;
    struct NodeListItem* prev;
};

// Move to general library eventually
struct NodeList* createNodeList() {
    struct NodeList* node_list = malloc(sizeof(struct NodeList));
    node_list->head = NULL;
    node_list->tail = NULL;
    if (pthread_mutex_init(&node_list->lock, NULL) !=0) {
        fprintf(stderr, "createNodeList: Failure to initialize mutex\n");
        exit(1); 
    }
    else {
        return node_list;
    }
}

struct NodeListItem* createNodeListItem(struct Node* e) {
    struct NodeListItem* item = malloc(sizeof(struct NodeListItem));
    item->node = e;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

// FOR TESTING ONLY
void printNodeList(struct NodeList* node_list) {
    struct NodeListItem *current;
    current = node_list->head;
    while (current != NULL) {
        printf("%s\n", current->node->data); 
        current = current->next;
    }
}

int length(struct NodeList* node_list) {
    int length = 0;
    struct NodeListItem *current;
    current = node_list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

bool empty(struct NodeList* node_list) {
    struct NodeListItem *current;
    current = node_list->head;
    return (current == NULL);
}

struct Node* removeFirst(struct NodeList* node_list) {
    struct NodeListItem *head;
    head = node_list->head;
    if (head) {
        node_list->head = head->next;
        node_list->head->prev = NULL;
        return head->node;
    } else { 
        // NEED TO HANDLE THE CASE WHERE HEAD DOESNT EXIST, EMPTY LIST 
        exit(1); // ?
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

// WHY WAS APPEND ORIGINALLY AN INT TYPE IF PREPEND WAS VOID?
// Changed names since stdio.h has append and prepend
// What about error handling? What if e is null?
void appendNode(struct NodeList* node_list, struct Node* e) {
    struct NodeListItem* new_last = createNodeListItem(e);
    if (!empty(node_list)) {
        // if list not empty;
        new_last->prev = node_list->tail;
        struct NodeListItem *old_last = malloc(sizeof(struct NodeListItem));
        old_last = node_list->tail;
        old_last->next = new_last;
        node_list->tail = new_last;
    } else {
        // if list is empty;
        node_list->head = new_last;
        node_list->tail = new_last;
    }
    return;
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

// https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_program_in_c.htm