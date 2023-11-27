#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "process.h"
#include "queue.h"
#include "json.h"
#include "graph.h"
#include "mock.h"
#include "stringBuffer.h"
#include "dynamicArray.h"
#include "html.h"

#define QUANTUM 4
#define CPU_HIGH 0
#define CPU_LOW 1
#define IO_DISK 2
#define IO_TAPE 3
#define IO_PRINT 4
#define IO_NONE 5
#define IO_TIME_DISK 2
#define IO_TIME_TAPE 5
#define IO_TIME_PRINT 10



void add_new_processes
(
        ProcessQueue*,     /* source queue (processes waiting to start) */
        ProcessQueue**,    /* destination queues (CPU and IO queues) */
        int                /* time elapsed since start of simulation */
);


void update_io_wait_time
(
        ProcessQueue**, /* array of queues including IO queues */
        int             /* time units since last update */
);


void update_io_queue
(
        ProcessQueue* pq,         /* pointer to IO queue */
        int time_since_update     /* time units since last update */
);


/* Transfer all processes that are done with IO to CPU queues
 * according to IO type */
void transfer_ready_processes(ProcessQueue**);


/* returns 1 if first process in queue has time_until_ready == 0, else returns 0 */
int has_ready_process(ProcessQueue*);

/* Selects and returns next process to be run from CPU queues */
Process* get_next_process(ProcessQueue**);


/* Advance time until process is over, has IO or is preempted,
 * update process accordingly and output run data */
void run_process
(
        Process*, /* process to be ran */
        Graph*,   /* adress for output of graph data */ 
        int*      /* adress of time elapsed since start of simulation */
);


/* Insert process into queues according to its io_status:
 * if IO_NONE or IO_DISK, insert it into CPU_LOW,
 * otherwise insert it into CPU_HIGH */
void requeue_process
(
        Process*,      /* source */
        ProcessQueue** /* destination (IO and CPU queues) */
);


/* Outputs graph as "time pid\ntime pid\n ..." to stdout, for now */
void output_graph(Graph*);


#endif
