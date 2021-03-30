#include <stdlib.h>
#include <stdio.h>
#include "../node.h"

void printNode (struct Node* node) {
    printf("%s\n", node->visited ? "true" : "false");
    printf("%d\n", node->id);
    printf("%s", node->data);
}

int main() {
    //this is for testing purposes for createNode
    char greeting[] = "Hello\n";
    struct Node* temp;
    bool temporary;
    struct Node* temp2;

    temp = createNode(greeting);
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
    temp2 = createNode(greeting);
    printNode(temp2);    
    temporary = nodeEquals(temp, temp2);
    printf("%s", temporary ? "true\n" : "false\n");

    temporary = nodeEquals(temp, temp);
    printf("%s", temporary ? "true\n" : "false\n");

    return 0;
}
