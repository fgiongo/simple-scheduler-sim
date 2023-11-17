#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"
#include "json.h"

static ProcessQueue *high_priority;
static ProcessQueue *low_priority;
static ProcessQueue *io_disk;
static ProcessQueue *io_tape;
static ProcessQueue *io_print;
static int global_time;

void init_global_queues(void);
void add_new_processes(Process*);
void update_queues(void);
Process* get_next_process(void);
Graph* run_process(Process*);
void requeue_process(Process*);
void output_graph(Graph*);

#endif
