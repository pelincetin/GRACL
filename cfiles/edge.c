#include "edge.h"

void updateEdge(struct Edge* edge, double new_weight) {
    if (edge->deleted) {
        fprintf(stderr, "updateEdge: Edge deleted\n");
        exit(1);
    }
    edge->weight = new_weight;
    return;
}

double weight(struct Edge* edge) {
    if (edge->deleted) {
        fprintf(stderr, "weight: Edge deleted\n");
        exit(1);
    }
    return edge->weight;
}

bool edgeEquals(struct Edge* e1, struct Edge* e2) {
    if ((e1->deleted) || (e2->deleted)) {
        fprintf(stderr, "edgeEquals: Edge deleted\n");
        exit(1);
    }
    return (((e1->weight == e2->weight) && nodeEquals(e1->start, e2->start)) && nodeEquals(e1->end, e2->end));
}

/* New start and end accessors */
struct Node* start(struct Edge* edge) {
    if (edge->deleted) {
        fprintf(stderr, "start: Edge deleted\n");
        exit(1);
    }
    return edge->start;
}

struct Node* end(struct Edge* edge) {
    if (edge->deleted) {
        fprintf(stderr, "end: Edge deleted\n");
        exit(1);
    }
    return edge->end;
}