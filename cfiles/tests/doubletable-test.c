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

    struct DoubleTable* dt = createDoubleTable(5);

    // test hashcode
    if(hashCode(dt, node1) != (node1->id % dt->size)){
        success = false;
    }
    if(hashCode(dt, node2) != (node2->id % dt->size)){
        success = false;
    }
    if(hashCode(dt, node3) != (node3->id % dt->size)){
        success = false;
    }

    // test insert with collisions
    insert(dt, node1, 1.0);
    insert(dt, node2, 2.0);
    insert(dt, node3, 3.0);
    insert(dt, node4, 4.0);
    insert(dt, node5, 5.0);
    insert(dt, node6, 6.0);
    insert(dt, node7, 7.0);
    insert(dt, node8, 8.0);
    insert(dt, node9, 9.0);
    insert(dt, node10, 10.0);
    insert(dt, node10, 10.0); // try inserting same node twice -- what happens? node10 appended to end twice?

    // test includes
    if (!includes(dt, node1) || !includes(dt, node7) || !includes(dt, node10)) {
        success = false;
    }

    // test get
    double get1 = get(dt, node1);
    double get8 = get(dt, node8);
    double get3 = get(dt, node3);
    if ((get1 != 1.0) || (get8 != 8.0) || (get3 != 3.0)) {
        success = false;
    }

    // test delete
    delete(dt, node1);
    delete(dt, node2);
    delete(dt, node3);
    delete(dt, node4);
    delete(dt, node1); // try deleting same node twice
    if (includes(dt, node1)) {
        success = false;
    }
    if (length_NL(keys(dt)) != 7) {
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