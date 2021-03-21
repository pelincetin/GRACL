#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_t tid[2];
int counter;

int synch_start(){
     if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    pthread_mutex_lock(&lock);
    return 0;
}

int synch_end(){
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    return 0;
}

void* testSync(void *arg)
{
    synch_start();

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++);

    printf("\n Job %d finished\n", counter);

    synch_end();

    return NULL;
}

int main(){
    // testing of synch
    int i = 0;
    int err;
    
    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &testSync, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}
