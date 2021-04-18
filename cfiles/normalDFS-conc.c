#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../graclstdlib.c"

int normalDFS(struct Node* current, struct Node* goal, struct NodeList* mypath){
    return 0;
}


//THIS HAS TO BE DONE BY THE COMPILER
struct normalDFSArgs {
    struct Node* current;
    struct Node* goal; 
    struct NodeList* mypath;
};

void *normalDFS_unwrapper(void *args) {
    struct normalDFSArgs *fargs = (struct normalDFSArgs *) args;

    normalDFS(fargs->current, fargs->goal, fargs->mypath);
    return NULL;
}


int main(){
    struct Node* goal; //assume it's initialized here
    struct NodeList* mypath = createNodeList();
    struct NodeList* possible_start = createNodeList();
    //append stuff to the nl


    //this is where it starts
    int len_possible_start = length_NL(possible_start);
    pthread_t* threads = malloc(sizeof(pthread_t) * len_possible_start);
    
    //done by the compiler
    struct normalDFSArgs* dfsargs = malloc(sizeof(struct normalDFSArgs) * len_possible_start);
    
    struct NodeListItem* currentNode = possible_start->head;
    int i = 0;
    while(currentNode){

        //done by the compiler
        dfsargs[i].current = currentNode->node;
        dfsargs[i].goal = goal;
        dfsargs[i].mypath = mypath;


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