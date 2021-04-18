#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

// HATCH

hatch nodelist func(arg1, arg2, arg3, arg4....) {

}

nodelist func(node current, node goal) {
    print(current.data)
}
// iSSUE: DO WE ENFORCE THAT FIRST ARG IS A NODE?
// HOW ELSE CAN THIS BE DONE??


pthread_t* arr; 

int hatch_start(int len, HOW_TO_PASS_FUNC, HOW_TO_PASS_ARGS, NODELIST?) {
    pthread_t* pthreadArray[len];
    arr = pthreadArray;
    // 1st. empty array
    // put threads in here
    // make array global variable, length is length of nodelist

    //  forloop where we make pthreads
    int i;
    for (i = 0; i < len; i++) {
        err = pthread_create(&(arr[i]), NULL, &func, NEED_ARGS, NODE_IN_NODELIST?);
        if (err != 0) {
            printf("\ncan't create thread :[%s]", strerror(err));
            return -1;
        } 
    }
    // the function associated with them is func
    // func is called on the args within it and then node at the end from nodelist
}

int hatch_end(int len) {
    // call pthread_join on the array
    for (j = 0; j < len; j++) {
        pthread_join(&arr[j], NULL);
    }   
}

*/