#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

int main(){
    bool success = true;

    struct Graph* g = createGraph(10);
    char nodedata1[] = "noded1";
    char nodedata2[] = "noded2";
    char nodedata3[] = "noded3";
    char nodedata4[] = "noded4";
    char nodedata5[] = "noded5";
    char nodedata6[] = "noded6";
    char nodedata7[] = "noded7";
    char nodedata8[] = "noded8";
    char nodedata9[] = "noded9";
    char nodedata10[] = "noded10";
    struct Node* node1 = createNode(g, nodedata1);
    struct Node* node2 = createNode(g, nodedata2);
    struct Node* node3 = createNode(g, nodedata3);
    struct Node* node4 = createNode(g, nodedata4);
    struct Node* node5 = createNode(g, nodedata5);
    struct Node* node6 = createNode(g, nodedata6);
    struct Node* node7 = createNode(g, nodedata7);
    struct Node* node8 = createNode(g, nodedata8);
    struct Node* node9 = createNode(g, nodedata9);
    struct Node* node10 = createNode(g, nodedata10);

    struct IntTable* it = createIntTable(5);

    // test hashcode
    if(hashCode(it, node1) != (node1->id % it->size)){
        success = false;
    }
    if(hashCode(it, node2) != (node2->id % it->size)){
        success = false;
    }
    if(hashCode(it, node3) != (node3->id % it->size)){
        success = false;
    }

    // test insert with collisions
    insert(it, node1, 1);
    insert(it, node2, 2);
    insert(it, node3, 3);
    insert(it, node4, 4);
    insert(it, node5, 5);
    insert(it, node6, 6);
    insert(it, node7, 7);
    insert(it, node8, 8);
    insert(it, node9, 9);
    insert(it, node10, 10);
    insert(it, node10, 10); // try inserting same node twice -- what happens? node10 appended to end twice?

    // test includes
    if (!includes(it, node1) || !includes(it, node7) || !includes(it, node10)) {
        success = false;
    }

    // test get
    double get1 = get(it, node1);
    double get8 = get(it, node8);
    double get3 = get(it, node3);
    if ((get1 != 1) || (get8 != 8) || (get3 != 3)) {
        success = false;
    }

    // test delete
    delete(it, node1);
    delete(it, node2);
    delete(it, node3);
    delete(it, node4);
    delete(it, node1); // try deleting same node twice
    if (includes(it, node1)) {
        success = false;
    }
    if (length_NL(keys(it)) != 7) {
        success = false;
    }

    if (success) {
        printf("SUCCESS\n");
    }
    else {
        printf("FAILURE\n");
    }

    return 0;
}