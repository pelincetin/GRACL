#include <stdlib.h>
#include <stdio.h>
#include "../doubletable.c"
#include "print-functions.c"

int main(){
    struct DoubleTable* dt = malloc(sizeof(struct DoubleTable));

    dt = createDoubleTable(20);
    return 0;
}
