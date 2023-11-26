#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"

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
    int i, new_bufsize;
    int* new_time;
    int* new_pid;

    if (!graph || !graph->time || !graph->pid || bufsize < 1) {
        fprintf(stdout, "graph_overflow(): bad argument\n");
        exit(1);
    }

    new_bufsize = graph->bufsize * 2;
    new_time = (int*) malloc(sizeof(int) * new_bufsize);
    if (!new_time) {
        fprintf(stdout, "graph_overflow(): bad alloc\n");
        exit(1);
    }

    new_pid = (int*) malloc(sizeof(int) * new_bufsize);
    if (!new_time) {
        free(new_time);
        fprintf(stdout, "graph_overflow(): bad alloc\n");
        exit(1);
    }

    for (i = 0; i < graph->n_elem; ++i) {
        new_time[i] = graph_get_time(i, graph);
        pid[i] = graph_get_pid(i, graph);
    }

    free(graph->time);
    free(graph->pid);
    graph->time = new_time;
    graph->pid = new_pid;
}


int graph_get_time(int n, Graph* graph){
    if (!graph || !graph->time){
        fprintf(stdout, "graph_get_time(): bad argument\n");
        exit(1);
    }

    if (n >= graph->n_elem) {
        fprintf(stdout, "graph_get_time(): out of bounds access\n");
        exit(1);
    }

    return (graph->time[n]);
}


int graph_get_pid(int n, Graph* graph){
    if (!graph || !graph->pid){
        fprintf(stdout, "graph_get_pid(): bad argument\n");
        exit(1);
    }

    if (n >= graph->n_elem) {
        fprintf(stdout, "graph_get_pid(): out of bounds access\n");
        exit(1);
    }

    return (graph->pid[n]);
}
