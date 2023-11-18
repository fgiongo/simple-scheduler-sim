#ifndef GRAPH_H
#define GRAPH_H

typedef struct _Graph {
    int n_elem;
    int bufsize;
    int* time;
    int* pid; 
} Graph;

Graph* graph_create(void);
void graph_overflow(Graph* graph);
void graph_append(int time, int pid, Graph* dest);

#endif
