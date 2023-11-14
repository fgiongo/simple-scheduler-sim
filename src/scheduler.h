#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_queue.h"

void handle_next_instruction(void);

int global_pid;
int global_n_processes;
ProcessQueue global_queues[3];

#endif
