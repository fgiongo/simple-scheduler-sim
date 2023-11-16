#ifndef QUEUE_H
#define QUEUE_H
#include "process.h"

typedef struct _ProcessQueue {
    Process **buf;
    int bufsize;
    int head;
    int end;
    int n_elem;
} ProcessQueue;

void pq_init(ProcessQueue*);
void pq_overflow(ProcessQueue*); /* Be aware: this function assumes queue is completely full */
void pq_underflow(ProcessQueue*);
void pq_insert(Process*, ProcessQueue*);
Process* pq_remove(ProcessQueue*);
void pq_kill_all_children(int ppid, ProcessQueue*);

#endif
