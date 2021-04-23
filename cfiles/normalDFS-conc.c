#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "../graclstdlib.c"
#include "tests/print-functions.c"

bool goalTest(struct Node* goal, struct Node* current){
    return nodeEquals(current, goal);
}

int normalDFS(struct Node* current, struct Node* goal, bool initialize){
    if(!initialize){
        initialize = true;
        fprintf(stderr, "hello1\n");
        struct NodeList* path = createNodeList();
        fprintf(stderr, "hello2\n");
    }
    fprintf(stderr, "hello3\n");
    appendNode(path, current);
    fprintf(stderr, "hello4\n");

    if (goalTest(goal, current)){
        printNodeList(path);
        fprintf(stderr, "hello10\n");
        return 0;
    }else{
        fprintf(stderr, "hello5\n");
        _synch_start((void*)current);
        fprintf(stderr, "hello6\n");
        if(updateVisited(current, true) < 0){
            return -1;
        }
        _synch_end((void*)current);
        fprintf(stderr, "hello7\n");

        struct EdgeListItem* currentEdgeItem = current->edges->head;
        while (currentEdgeItem) {
            fprintf(stderr, "hello8\n");
            struct Edge* currentEdge = currentEdgeItem->edge;
            struct Node* adjacentNode = currentEdge->end;

            bool alreadyVisited = false;
            _synch_start((void*)adjacentNode);
            alreadyVisited = visited(adjacentNode);
            _synch_end((void*)adjacentNode);

            if(!alreadyVisited){
                normalDFS(adjacentNode, goal, true);
            }
            currentEdgeItem = currentEdgeItem->next;
        }
    }
    return 0;
}

//THIS HAS TO BE DONE BY THE COMPILER
struct normalDFSArgs {
    struct Node* current;
    struct Node* goal; 
    bool initialize;
};

void *normalDFS_unwrapper(void *args) {
    struct normalDFSArgs *fargs = (struct normalDFSArgs *) args;

    normalDFS(fargs->current, fargs->goal, fargs->initialize);
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
    struct Node* node10;
    struct Edge* e1;
    struct Edge* e2;
    struct Edge* e3;
    struct Edge* e4;
    struct Edge* e5;
    struct Edge* e6;
    struct Edge* e7;
    struct Edge* e8;
    struct Edge* e9;
    g = createGraph(12);
    node1 = createNode(g, "A");
    node2 = createNode(g, "B");
    node3 = createNode(g, "C");
    node4 = createNode(g, "D");
    node5 = createNode(g, "E");
    node6 = createNode(g, "F");
    node7 = createNode(g, "G");
    node8 = createNode(g, "H");
    node9 = createNode(g, "I");
    node10 = createNode(g, "J");
    e1 = addEdge(g, node1, node2, 14.0);
    e2 = addEdge(g, node2, node5, 13.0);
    e3 = addEdge(g, node5, node9, 43.0);
    e4 = addEdge(g, node1, node3, 13.0);
    e5 = addEdge(g, node3, node6, 43.0);
    e6 = addEdge(g, node3, node7, 13.0);
    e7 = addEdge(g, node6, node10, 43.0);
    e8 = addEdge(g, node1, node4, 13.0);
    e9 = addEdge(g, node4, node8, 43.0);

    struct Node* goal = node7; 
    struct NodeList* possible_start = createNodeList();
    appendNode(possible_start, node1); //A
    appendNode(possible_start, node9); //I
    appendNode(possible_start, node8); //H

    // this is where it starts
    int len_possible_start = length_NL(possible_start);
    pthread_t* threads = malloc(sizeof(pthread_t) * len_possible_start);
    
    // done by the compiler
    struct normalDFSArgs* dfsargs = malloc(sizeof(struct normalDFSArgs) * len_possible_start);
    
    struct NodeListItem* currentNode = possible_start->head;
    int i = 0;
    while (currentNode) {
        // done by the compiler
        dfsargs[i].current = currentNode->node;
        dfsargs[i].goal = goal;
        dfsargs[i].initialize = false;

        pthread_create(threads + i, NULL, normalDFS_unwrapper, dfsargs + i);
        currentNode = currentNode->next;
        i++;
    }
    
    for (int i = 0; i< len_possible_start; i++){
        pthread_join(threads[i], NULL);
    }

}

/* TODO
1. get every single warning, get this c program to work
2. run clang on it --> .ll file
3. add the type to codegen 
*/