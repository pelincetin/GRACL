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
    if(hashCode_it(it, node1) != (node1->id % it->size)){
        success = false;
    }
    if(hashCode_it(it, node2) != (node2->id % it->size)){
        success = false;
    }
    if(hashCode_it(it, node3) != (node3->id % it->size)){
        success = false;
    }

    // test insert with collisions
    insertInt(it, node1, 1);
    insertInt(it, node2, 2);
    insertInt(it, node3, 3);
    insertInt(it, node4, 4);
    insertInt(it, node5, 5);
    insertInt(it, node6, 6);
    insertInt(it, node7, 7);
    insertInt(it, node8, 8);
    insertInt(it, node9, 9);
    insertInt(it, node10, 10);
    insertInt(it, node10, 10); // try inserting same node twice -- what happens? node10 appended to end twice?

    // test includes
    if (!inInt(it, node1) || !inInt(it, node7) || !inInt(it, node10)) {
        success = false;
    }

    // test get
    double get1 = getInt(it, node1);
    double get8 = getInt(it, node8);
    double get3 = getInt(it, node3);
    if ((get1 != 1) || (get8 != 8) || (get3 != 3)) {
        success = false;
    }

    // test delete
    deleteInt(it, node1);
    deleteInt(it, node2);
    deleteInt(it, node3);
    deleteInt(it, node4);
    deleteInt(it, node1); // try deleting same node twice
    if (inInt(it, node1)) {
        success = false;
    }
    if (length_NL(intKeys(it)) != 7) {
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