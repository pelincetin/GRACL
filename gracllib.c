#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO: The idea here is that these functions would be invoked with a pointer
// to the lock associated with whatever object synch is called upon 

// pthread_t tid[2];
// int counter;

// TODO: Do we want to init here or when object is created
// Is this for Pelin+Maya or Defne+Pelin
// Should we init and destroy every time synch is called 

int synch_init(pthread_mutex_t* lock) {
    if (pthread_mutex_init(lock, NULL) != 0) {
        printf("\n mutex init failed\n");
        return -1;
    }
    return 0;
}

int synch_start(pthread_mutex_t* lock) {
    if (pthread_mutex_lock(lock) != 0) {
        printf("\n locking failed\n");
        return -1;
    }
    return 0;
}

int synch_end(pthread_mutex_t* lock) {
    if(pthread_mutex_unlock(lock) != 0) {
        printf("\n mutex is not valid, unlock failed\n");
        return -1;
    }
    return 0;
}

int synch_destroy(pthread_mutex_t* lock) {
    if (pthread_mutex_destroy(lock) != 0) {
        printf("\n mutex is not valid, destroy failed\n");
        return -1;
    }
    return 0;
}

/*
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

    synch_init();

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &testSync, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    synch_destroy();

    return 0;
}
*/