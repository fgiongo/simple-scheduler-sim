#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include "process.h"

typedef struct _ProcessQueue{
    int n_elem;
    Process **list; /* list of pointers to processes */
} ProcessQueue;

void process_queue_init(ProcessQueue *pq);

#endif
