#include <stdlib.h>
#include <stdio.h>
#include "../inttable.c"
#include "print-functions.c"

int main(){
    struct IntTable* it = malloc(sizeof(struct IntTable));
    struct Node* n = malloc(sizeof(struct Node));

    it = createIntTable(20);

    //insert();
    return 0;
}
