#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_queue.h"

void handle_next_instruction(void);

static int global_pid;
static int global_n_processes;
static ProcessQueue *global_queues;

#endif
