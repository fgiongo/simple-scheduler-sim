#include <stdio.h>
#include <stdlib.h>
#include "../queue.h"

int main(void) {
    int i;
    int n_proc;
    int *pid_list;
    Process* proc;
    Process* tmp;
    ProcessQueue* pq;

    n_proc = 32;

    pq = (ProcessQueue*) malloc(sizeof(ProcessQueue));
    proc = (Process*) malloc(sizeof(Process) * n_proc);

    for (i = 0; i < n_proc; ++i) {
        proc[i].pid = i + 1;
        proc[i].ppid = 0;
    }

    pq_init(pq);
    pq_insert(&proc[0], pq);

    i = pq->head;
    if (pq->buf[i]->pid == 1 && pq->buf[i]->ppid == 0) {
        fprintf(stdout, "ProcessQueue: Insertion on empty queue: passed =)\n");
    }
    else {
        fprintf(stdout, "ProcessQueue: Insertion on empty queue: failed =(\n");
    }

    pq_insert(&proc[1], pq);
    i = pq->head;
    if (pq->buf[i+1]->pid == 2
        && pq->buf[i+1]->ppid == 0
        && pq->end == 0)
    {
        fprintf(stdout, "ProcessQueue: Insertion on queue with one element, with overflow: passed =)\n");
    }
    else {
        fprintf(stdout, "ProcessQueue: Insertion on queue with one element, with overflow: failed =(\n");
    }

    pq_insert(&proc[2], pq);
    i = pq->head;
    if (pq->buf[i+2]->pid == 3
        && pq->buf[i+2]->ppid == 0
        && pq->end == 3)
    {
        fprintf(stdout, "ProcessQueue: Insertion on queue with two elements, with overflow: passed =)\n");
    }
    else {
        fprintf(stdout, "ProcessQueue: Insertion on queue with two elements, with overflow: failed =(\n");
    }

    pq_insert(&proc[3], pq);
    i = pq->head;
    if (pq->buf[i+3]->pid == 4
        && pq->buf[i+3]->ppid == 0
        && pq->end == 0)
    {
        fprintf(stdout, "ProcessQueue: Insertion on queue with three elements, without overflow: passed =)\n");
    }
    else {
        fprintf(stdout, "ProcessQueue: Insertion on queue with three elements, without overflow: failed =(\n");
    }

    pq_remove(pq);
    i = pq->head;
    if (pq->buf[i]->pid == 2
        && pq->head == 1
        && pq->buf[i]->ppid == 0
        && pq->end == 0)
    {
        fprintf(stdout, "ProcessQueue: Removal on queue with four elements: passed =)\n");
    }
    else {
        fprintf(stdout, "ProcessQueue: Removal on queue with four elements: failed =(\n");
    }

    pq_remove(pq);
    i = pq->head;
    if (pq->buf[i]->pid == 3
        && pq->head == 0
        && pq->buf[i]->ppid == 0
        && pq->end == 0
        && pq->n_elem == 2)
    {
        fprintf(stdout, "ProcessQueue: Removal on queue with three elements, with overflow: passed =)\n");
    }
    else {
        fprintf(stdout, "ProcessQueue: Removal on queue with three elements, with overflow: failed =(\n");
    }

    pq_insert(&proc[0], pq);
    pq_insert(&proc[1], pq);

    tmp = pq_get_element(3, pq);
    if (tmp->pid == 2) {
        fprintf(stdout, "ProcessQueue: random access: passed =)\n");
    }

    for (i = 4; i < n_proc; ++i) {
        pq_insert(&proc[i], pq);
    }

    pid_list = (int*) calloc(n_proc, sizeof(int));
    if (!pid_list) {
        fprintf(stderr, "main(): bad alloc");
        exit(1);
    }

    for (i = 0; i < n_proc; ++i) {
        tmp = pq_remove(pq);
        pid_list[i] = tmp->pid;
    }

    if (pid_list[0] == 3
        && pid_list[1] == 4
        && pid_list[2] == 1
        && pid_list[3] == 2)
    {
        fprintf(stdout, "ProcessQueue: Multiple insertions and removals: passed =)\n");
    }
    else {
        fprintf(stdout, "ProcessQueue: Multiple insertions and removals: failed =(\n");
    }

    return 0;
}
