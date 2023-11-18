#include "graph.h"

Graph* graph_create(void){
    Graph* graph;
    int* time;
    int* pid;

    graph = (Graph*) malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "graph_create(): bad alloc\n");
        exit(1);
    }

    time = (int*) malloc(sizeof(int));
    pid = (int*) malloc(sizeof(int));
    if (!time || !pid){
        fprintf(stderr, "graph_create(): bad alloc\n");
        exit(1);
    }

    graph->n_elem = 0;
    graph->bufsize = 1;
    graph->time = time;
    graph->pid = pid;

    return graph;
}


void graph_append
(
        int time,
        int pid,
        Graph* dest
)
{
    /* TODO(nando): implement this */
}

void graph_overflow(Graph* graph){
    /* TODO(nando): implement this */
}
