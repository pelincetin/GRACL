#include <stdlib.h>
#include <string.h>

struct Edge
{
    double weight; 
    struct Node start; // Should these be pointers to nodes?
    struct Node end;
    /* Mutex?? */
};