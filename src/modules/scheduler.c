#include "scheduler.h"


/* Checks first process in source queue.
 * If creation_time <= time_elapsed, inserts new process into CPU_HIGH
 * queue and repeats this until the first process in source queue satisfies
 * creation_time > time_elapsed */
void add_new_processes
(
        ProcessQueue* new_processes, /* source queue (processes waiting to start) */
        ProcessQueue** queues,       /* destination queues (CPU and IO queues) */
        int time_elapsed             /* time elapsed since start of simulation */
)
{
    Process* p;
    if (!new_processes
        || !new_processes->buf
        || !queues)
    {
        fprintf(stderr, "scheduler:add_new_processes(): bad argument\n");
        exit(1);
    }

    while (new_processes->n_elem > 0)
    {
        p = pq_get_element(0, new_processes);

        if (p->creation_time <= time_elapsed) {
            p = pq_remove(new_processes);
            pq_insert(p, queues[CPU_HIGH]);
        }
        else {
            break;
        }
    }
}


/* Updates time_until_ready in all processes of IO queues by subtracting
 * time units since last update. */
void update_io_wait_time
(
        ProcessQueue** queues, /* array of queues including IO queues */
        int time_since_update  /* time units since last update */
)
{
    /* TODO(nando): implement this */
}


/* Transfer all processes that are done with IO to CPU queues
 * according to IO type */
void transfer_ready_processes(ProcessQueue** queues){
    /* TODO(nando): implement this */
}


/* If CPU_HIGH and CPU_LOW queues are empty, returns NULL.
 * Otherwise, if CPU_HIGH queue is empty and CPU_LOW is not empty, 
 * returns first process in CPU_LOW.
 * Otherwise, if CPU_HIGH is not empty, returns first process in CPU_HIGH. */
Process* get_next_process(ProcessQueue** queues){
    /* TODO(nando): implement this */
    return NULL;
}


/* Increments cpu_time of process until it reaches the next IO operation,
 * (if exists), otherwise increments cpu time until it equals cpu_time_needed,
 * up to a maximum of QUANTUM time units.
 * Increments time_elapsed by the same amount of time units as cpu_time was incremented.
 * Retuns pairs of values (time, pid) where time = time_elapsed at every time
 * unit increment during the run, pid is current proceess' PID */
void run_process
(
        Process* proc,    /* process to be ran */
        Graph* output,    /* adress for output of graph data */ 
        int* time_elapsed /* adress of time elapsed since start of simulation */
)
{
    /* TODO(nando): implement this */
}


/* Insert process into queues according to its io_status:
 * if IO_NONE or IO_DISK, insert it into CPU_LOW,
 * otherwise insert it into CPU_HIGH */
void requeue_process
(
        Process* proc,      /* source */
        ProcessQueue** queues /* destination (IO and CPU queues) */
)
{
    /* TODO(nando): implement this */
}


/* Outputs graph as "time pid\ntime pid\n ..." to stdout, for now */
void output_graph(Graph* output){
    int tr, td;
    DynamicArrayPID arrayPid;

    StringBuffer stringHTML;
    StringBuffer stringHTML_Head;
    StringBuffer stringHTML_Body;
    initStringBuffer(&stringHTML, MIN_STRING_LENGTH);
    initStringBuffer(&stringHTML_Head, MIN_STRING_LENGTH);
    initStringBuffer(&stringHTML_Body, MIN_STRING_LENGTH);
    initDynamicArray(&arrayPid, 10);

    getNumTrTd(&tr, &td, (*output), &arrayPid);
    headBuilder(&stringHTML_Head);
    
    bodyBuilder(&stringHTML_Body, tr, td, (*output), arrayPid);

    saferCopy(&stringHTML, stringHTML_Head.string);
    saferConcat(&stringHTML, &stringHTML_Body);

    fputs(stringHTML.string, stdout);
}
