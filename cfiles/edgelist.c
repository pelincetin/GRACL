#include "edgelist.h"

struct EdgeList* createEdgeList() {
    struct EdgeList* edge_list = malloc(sizeof(struct EdgeList));
    edge_list->head = NULL;
    edge_list->tail = NULL;
    if (pthread_mutex_init(&edge_list->lock, NULL) !=0) {
        fprintf(stderr, "createEdgeList: Failure to initialize mutex\n");
        exit(1);
    }
    return edge_list;
}

struct EdgeListItem* createEdgeListItem(struct Edge* e) {
    struct EdgeListItem* item = malloc(sizeof(struct EdgeListItem));
    item->edge = e;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

struct Edge* head_EL(struct EdgeList* edge_list) { 
    if (!edge_list->head) {
        return NULL;
    }
    return edge_list->head->edge;
}

struct Edge* tail_EL(struct EdgeList* edge_list) {
    if (!edge_list->tail) {
        return NULL;
    }
    return edge_list->tail->edge;
}

struct Edge* removeFirst_EL(struct EdgeList* edge_list) {
    struct EdgeListItem *head;
    head = edge_list->head;
    if (head) {
        edge_list->head = head->next;
        if(edge_list->head){
            edge_list->head->prev = NULL;
        }
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
    if (e->deleted) {
        fprintf(stderr, "prependEdge: Edge deleted\n");
        exit(1);
    }
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

bool empty_EL(struct EdgeList* edge_list) {
    struct EdgeListItem *current;
    current = edge_list->head;
    return (current == NULL);
}

int length_EL(struct EdgeList* edge_list) {
    int length = 0;
    struct EdgeListItem *current;
    current = edge_list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int removeEdge(struct EdgeList* edge_list, struct Edge* e) {
    struct EdgeListItem* head = edge_list->head;
    struct EdgeListItem* prev = NULL;
    struct EdgeListItem* next = NULL;
    if(head == NULL) {
        // list is empty 
        return -1;
    } else {
        prev = head->prev;
        while (head) {
            bool equal = (e->weight == head->edge->weight) && (e->start->id == head->edge->start->id) && (e->end->id == head->edge->end->id);
            if (equal) {
                if (prev) {
                    next = head->next;
                    prev->next = next;
                    if (next) {
                        next->prev = prev;
                    }
                } else {
                    next = head->next;
                    edge_list->head = next;
                    if (next) {
                        next->prev = NULL;
                    }
                }
                return 0;
            }
            prev = head;
            head = head->next;
        }
        return -1;
    }
}

void appendEdge(struct EdgeList* edge_list, struct Edge* e) {
    if (e->deleted) {
        fprintf(stderr, "appendEdge: Edge deleted\n");
        exit(1);
    }
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
