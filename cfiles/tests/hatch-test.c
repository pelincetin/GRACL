#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

struct hatchArgs {
    struct Node* n; 
};

int start_routine(struct Node* n){
    printf("%s", data(n));
    return 0;
}

void *hatch_unwrapper(void *args) {
    struct hatchArgs *fargs = (struct hatchArgs *) args;

    start_routine(fargs->n);
    return NULL;
}

int main(){
    struct Graph* g;
    struct Node* node1;
    struct Node* node2;
    struct Node* node3;
    struct Node* node4;
    struct Node* node5;
    struct Node* node6;
    struct Node* node7;
    struct Node* node8;
    struct Node* node9;
    struct NodeList* nl;
    int i = 0;
    g = createGraph(10);
    node1 = createNode(g, "A");
    node2 = createNode(g, "B");
    node3 = createNode(g, "C");
    node4 = createNode(g, "D");
    node5 = createNode(g, "E");
    node6 = createNode(g, "F");
    node7 = createNode(g, "G");
    node8 = createNode(g, "H");
    node9 = createNode(g, "I");
    nl = nodes(g);
    int len_possible_start = length_NL(nl);

    pthread_t* threads = malloc(sizeof(pthread_t) * len_possible_start);
    
    struct NodeListItem* currentNode = nl->head;

    while(currentNode){
        pthread_create(threads + i, NULL, hatch_unwrapper, currentNode);
        currentNode = currentNode->next;
        i++;
    }

    hatch_end(threads, len_possible_start);
}