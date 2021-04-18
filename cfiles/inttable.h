#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUILDSTDLIB
#include "graph.h"
#endif

struct IntTable* createIntTable(int predicted_size);

int hashCode_it(struct IntTable* it, struct Node* node);

int getInt(struct IntTable* it, struct Node* n);

struct IntTableLLItem* createIntTableLLItem(struct Node* n, int data);

struct IntTableItem* createIntTableItem(struct Node* n, int data);

// technically complexity could improve if we insert in a sorted manner
// TODO
void insertInt(struct IntTable* it, struct Node* n, int data);

bool inInt(struct IntTable* it, struct Node* n);

int deleteInt(struct IntTable* it, struct Node* n);