#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main() {
    //this is for testing purposes for createNode
    char greeting[] = "Hello\n";
    struct Node* temp= malloc(sizeof(struct Node));
    bool temporary;
    struct Node* temp2= malloc(sizeof(struct Node));

    temp->data = greeting;
    temp->visited = false;
    temp->id=id_num;
    id_num++;
    printNode(temp); 

    //this is for testing updateData
    char hsm_forever[] = "zac efron\n";
    temp = updateData(hsm_forever, temp);
    printNode(temp);

    //this is for testing visited()
    temporary = visited(temp);
    printf("%s", temporary ? "true\n" : "false\n");

    //this is for testing updateVisited()
    temp = updateVisited(true, temp);
    temporary = visited(temp);
    printf("%s", temporary ? "true\n" : "false\n");

    // this is for testing equals()
    temp = updateData(greeting, temp);
    temp2->data = greeting;
    temp2->visited = false;
    temp2->id=id_num;
    id_num++;
    printNode(temp2);    
    temporary = nodeEquals(temp, temp2);
    printf("%s", temporary ? "true\n" : "false\n");

    temporary = nodeEquals(temp, temp);
    printf("%s", temporary ? "true\n" : "false\n");

    return 0;
}
