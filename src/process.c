#include <stdio.h>
#include <stdlib.h>
#include "process.h"

void create_process(void){
    Process *p = (Process *) malloc(sizeof(Process));
    if (!p){
        fprintf(stderr, "create_process: could not create new process\n");
        exit(1);
    }
    process_init(p);
}

void process_init(Process *p){
    /* TODO: set up new process with random attributes (within reason),
             add new process to queues */
}

Process* fetch_next_process(void){
    /* TODO: fetch next process from queues, update queues */
    return NULL;
}

void process_destroy(Process *p){
    /* TODO: free all the things */
}
