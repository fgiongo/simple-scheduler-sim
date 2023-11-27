#ifndef QUEUE_H
#define QUEUE_H

typedef struct _ProcessQueue {
    Process **buf;
    int bufsize;
    int head;
    int end;
    int n_elem;
} ProcessQueue;

ProcessQueue* pq_create(void);
void pq_overflow(ProcessQueue*); /* Be aware: this function assumes queue is completely full */
void pq_underflow(ProcessQueue*);
void pq_insert(Process*, ProcessQueue*);
Process* pq_remove(ProcessQueue*);
Process* pq_get_element(int index, ProcessQueue*);
void pq_print(ProcessQueue *pq);

#endif
