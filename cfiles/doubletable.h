#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "graph.h"
#endif

struct DoubleTable* createDoubleTable(int predicted_size);

int hashCode_dt(struct DoubleTable* dt, struct Node* node);

double getDouble(struct DoubleTable* dt, struct Node* n);

struct DoubleTableLLItem* createDoubleTableLLItem(struct Node* n, double data);

struct DoubleTableItem* createDoubleTableItem(struct Node* n, double data);

// technically complexity could improve if we insert in a sorted manner
// TODO
void insertDouble(struct DoubleTable* dt, struct Node* n, double data);

struct NodeList* doubleKeys(struct DoubleTable* dt);

bool inDouble(struct DoubleTable* dt, struct Node* n);

int deleteDouble(struct DoubleTable* dt, struct Node* n);

