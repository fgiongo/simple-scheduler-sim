#include "scheduler.h"


/* TODO: initialize all global queues*/
void init_global_queues(void){}

/* TODO: initilize graph */
void init_graph(Graph* graph){}

/* TODO: adds all new processes to priority queues */
void add_new_processes(Process* proc){}

/* TODO: transfers ready processes from IO queues to CPU queues */
void update_queues(void){}

/* TODO: returns first process in high priority queue
 *       if it is empty, returns first process in low priority queue
 *       if it is also empty, returns NULL */
Process* get_next_process(void){
    return NULL;
}

/* TODO: increments time until process requires IO,
 *       or until the cpu_time = running_time (process is done)
 *       or until quantum is reached
 *       returns graph with (time, pid) values for the run */
Graph* run_process(Process* proc){
    return NULL;
}


/* TODO: requeue process to low priority queue if not blocked,
 *       otherwise requeue to correct IO queue */
void requeue_process(Process* proc){}

void output_graph(Graph* graph){}
