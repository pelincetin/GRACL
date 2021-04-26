#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int counter = 0;

void* testSync(void *arg)
{
    struct Node* node1 = (struct Node*) arg;
    _synch_start(arg);

    unsigned long i = 0;
    counter += 1;
    printf("Thread %d started\n", counter);
    printf("Printing the node: %s\n", node1->data);
    updateData(node1, "i'm an updated node\n");
    printf("Printing the node after data has been updated: %s\n", node1->data);

    for(i=0; i<(0xFFFFFFFF);i++);

    printf("Thread %d finished\n", counter);

    _synch_end(arg);

    return NULL;
}

int main(){
    // testing of synch
    struct Node* node1;
    struct Graph* g;
    int err;
    int i = 0;
    char hello[] = "Hello\n";
    pthread_t tid[2];

    g = createGraph(10);
    node1 = createNode(g, hello);

    pthread_mutex_t* pm = _convert_to_lockable((void*)node1);

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &testSync, (void*)pm);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    hatch_end(tid, 2);
    synch_destroy(pm);

    return 0;
}
