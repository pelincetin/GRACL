#include <stdlib.h>
#include <stdio.h>
#include "../../graclstdlib.c"
#include "print-functions.c"

/*
int hashCode_dt(struct DoubleTable* dt, struct Node* node)
double get(struct DoubleTable* dt, struct Node* n)
struct DoubleTableLLItem* createDoubleTable(struct Node* n, double data)
void insert(struct DoubleTable* dt, struct Node* n, double data)
struct NodeList* keys(struct DoubleTable* dt)
bool includes(struct DoubleTable* dt, struct Node* n)
int delete(struct DoubleTable* dt, struct Node* n)
*/

int main(){
    bool success = true;

    struct Graph* g = createGraph(100);
    char nodedata1[] = "noded1";
    char nodedata2[] = "noded2";
    char nodedata3[] = "noded3";
    char nodedata4[] = "noded4";
    struct Node* node1 = createNode(g, nodedata1);
    struct Node* node2 = createNode(g, nodedata2);
    struct Node* node3 = createNode(g, nodedata3);
    struct Node* node4 = createNode(g, nodedata4);

    struct DoubleTable* dt = createDoubleTable(3);
    insert(dt, node1, 1.0);
    insert(dt, node2, 2.0);
    insert(dt, node3, 3.0);
    // insert(dt, node4, 4.0);

    double get1 = get(dt, node1);
    double get2 = get(dt, node2);
    double get3 = get(dt, node3);
    if ((get1 != 1.0) || (get2 != 2.0) || (get3 != 3.0)) {
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