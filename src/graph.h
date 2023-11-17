#ifndef GRAPH_H
#define GRAPH_H

typedef struct _Graph {
    int size;
    int bufsize;
    int* values[2];
} Graph;

void graph_init(Graph* graph);
void graph_overflow(Graph* graph);
void graph_append(int src[2], Graph* dest);

#endif
