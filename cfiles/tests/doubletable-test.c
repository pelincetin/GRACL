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
    if(hashCode_dt(dt, node1) != (node1->id % dt->size)){
        success = false;
    }
    if(hashCode_dt(dt, node2) != (node2->id % dt->size)){
        success = false;
    }
    if(hashCode_dt(dt, node3) != (node3->id % dt->size)){
        success = false;
    }

    // test insert with collisions
    _insertDouble(dt, node1, 1.0);
    _insertDouble(dt, node2, 2.0);
    _insertDouble(dt, node3, 3.0);
    _insertDouble(dt, node4, 4.0);
    _insertDouble(dt, node5, 5.0);
    _insertDouble(dt, node6, 6.0);
    _insertDouble(dt, node7, 7.0);
    _insertDouble(dt, node8, 8.0);
    _insertDouble(dt, node9, 9.0);
    _insertDouble(dt, node10, 10.0);
    _insertDouble(dt, node10, 10.0); // insert same node twice -- node10 appended to end twice without issue

    // test inserting a node from a different graph
    /*
    struct Graph* g2 = createGraph(10);
    char nodedata11[] = "noded11";
    struct Node* node11 = createNode(g2, nodedata11);
    _insertDouble(dt, node11, 11.0); // GIVES AN ERROR (as it should)
    */

    // test includes
    if (!inDouble(dt, node1) || !inDouble(dt, node7) || !inDouble(dt, node10)) {
        success = false;
    }
    
    // test get
    double get1 = _getDouble(dt, node1);
    double get8 = _getDouble(dt, node8);
    double get3 = _getDouble(dt, node3);
    if ((get1 != 1.0) || (get8 != 8.0) || (get3 != 3.0)) {
        success = false;
    }

    removeNodeGraph(g, node4);
    if(!inDouble(dt, node4)){
        success = false;
    }

    
    // test delete
    deleteDouble(dt, node1);
    deleteDouble(dt, node2);
    deleteDouble(dt, node3);
    deleteDouble(dt, node4);
    deleteDouble(dt, node5);
    deleteDouble(dt, node6);
    deleteDouble(dt, node7);
    deleteDouble(dt, node8);
    deleteDouble(dt, node9);
    deleteDouble(dt, node10);
    deleteDouble(dt, node10); // try deleting same node (added to dt twice) twice
    deleteDouble(dt, node1); // try deleting same node (added to dt once) twice

    if (inDouble(dt, node1)) {
        success = false;
    }
    if (length_NL(doubleKeys(dt)) != 0) {
        success = false;
    }

    // test making an dt with a size of 0 or smaller
    //struct DoubleTable* dt2 = createDoubleTable(0);
    //struct DoubleTable* dt3 = createDoubleTable(-1);
    
    if (success) {
        printf("SUCCESS\n");
    }
    else {
        printf("FAILURE\n");
    }

    return 0;
}