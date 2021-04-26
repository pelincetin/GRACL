#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Lockable{
    pthread_mutex_t pm;
};

pthread_mutex_t* _convert_to_lockable(void* obj){
    struct Lockable* new;
    new = (struct Lockable*) obj;
    return &(new->pm);
}

int synch_start(pthread_mutex_t* lock) {
    if (pthread_mutex_lock(lock) != 0) {
        printf("\n locking failed\n");
        return -1;
    }
    return 0;
}

int _synch_start(void* obj){
    return synch_start(_convert_to_lockable(obj));
}

int synch_end(pthread_mutex_t* lock) {
    if(pthread_mutex_unlock(lock) != 0) {
        printf("\n mutex is not valid, unlock failed\n");
        return -1;
    }
    return 0;
}

int _synch_end(void* obj){
    return synch_end(_convert_to_lockable(obj));
}

int synch_destroy(pthread_mutex_t* lock) {
    if (pthread_mutex_destroy(lock) != 0) {
        printf("\n mutex is not valid, destroy failed\n");
        return -1;
    }
    return 0;
}

int hatch_end(pthread_t* thread_arr, int len) {
    int j;
    for (j = 0; j < len; j++) {
        pthread_join(thread_arr[j], NULL);
    }
    return 0;  
}
