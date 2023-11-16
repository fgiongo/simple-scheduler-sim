#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_queue.h"

static ProcessQueue *high_priority;
static ProcessQueue *low_priority;
static ProcessQueue *io;
static int time;

void init_queues(void);
Process* parse_JSON(void);
void update_priorities(void);
void add_new_processes(Process*);
void transfer_ready_processes(void); 
int all_queues_are_empty(void);
Process* get_process_from_queues(void);
int is_finished(Process*);
void kill_all_children(Process*);
void kill(Process*);
int needs_io(Process*);
void block_process(Process*);
int quantum_timed_out(Process*);
void return_to_queue(Process*);
void run_process(Process*);
void generate_output(Process*);

#endif
