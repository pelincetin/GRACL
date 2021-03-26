#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct LockedObject
{
    pthread_mutex lock;
}