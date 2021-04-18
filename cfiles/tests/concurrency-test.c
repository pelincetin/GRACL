#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* testSync(void *arg)
{
    synch_start(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++);

    printf("\n Job %d finished\n", counter);

    synch_end(&lock);

    return NULL;
}

int main(){
    // testing of synch
    int err;
    int i = 0;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return -1;
    }

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &testSync, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    synch_destroy(&lock);

    return 0;
}
