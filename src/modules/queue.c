#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

ProcessQueue* pq_create(void) {
    ProcessQueue* pq;
    pq = (ProcessQueue*) malloc(sizeof(ProcessQueue));
    if (!pq) {
        fprintf(stderr, "pq_create(): bad alloc\n");
        exit(1);
    }

    pq->buf = (Process**) malloc(sizeof(Process*));
    if (!pq->buf) {
        fprintf(stderr, "pq_create(): bad alloc\n");
        exit(1);
    }

    pq->bufsize = 1;
    pq->head = 0;
    pq->end = 0;
    pq->n_elem = 0;
    return pq;
}

void pq_overflow(ProcessQueue* pq) {
    int i, new_bufsize;
    Process** new_buf;
    Process* p;

    if (!pq) {
        fprintf(stderr, "pq_overflow(): bad argument\n");
        exit(1);
    }

    if (pq->bufsize <= 0 || pq->n_elem > pq->bufsize) {
        fprintf(stderr, "pq_overflow(): bad argument\n");
        exit(1);
    }

    new_bufsize = pq->bufsize * 2;
    new_buf = (Process**) calloc(new_bufsize, sizeof(Process*));
    if (!new_buf) {
        fprintf(stderr, "pq_overflow(): could not allocate new buffer\n");
        exit(1);
    }

    for (i = 0; i < pq->n_elem; ++i) {
        p = pq_get_element(i, pq);
        new_buf[i] = p;
    }

    free(pq->buf);
    pq->buf = new_buf;
    pq->bufsize = new_bufsize;
    pq->head = 0;
    pq->end = pq->n_elem;
}

void pq_underflow(ProcessQueue* pq) {
    Process** new_buf;
    Process* p;
    int new_bufsize, i;

    if (!pq) {
        fprintf(stderr, "pq_underflow(): bad argument\n");
        exit(1);
    }

    if (pq->n_elem * 2 > pq->bufsize) {
        fprintf(stderr, "pq_underflow(): bad argument\n");
        exit(1);
    }

    if (pq->n_elem == 0) {
        return;
    }

    new_bufsize = pq->bufsize / 2;
    new_buf = (Process**) malloc(sizeof(Process*) * new_bufsize);
    if (!new_buf) {
        fprintf(stderr, "pq_underflow(): bad alloc\n");
        exit(1);
    }

    for (i = 0; i < pq->n_elem; ++i) {
        p = pq_get_element(i, pq);
        new_buf[i] = p;
    }

    pq->head = 0;
    pq->end = pq->n_elem % new_bufsize;
    pq->bufsize = new_bufsize;
    free(pq->buf);
    pq->buf = new_buf;
    return;
}

void pq_insert(Process* proc, ProcessQueue* pq){
    int i;

    if (!proc || !pq) {
        fprintf(stderr, "pq_insert(): bad argument\n");
        exit(1);
    }

    if (pq->n_elem == 0) {
        if (pq->bufsize != 1
            || pq->head != 0
            || pq->end != pq->head)
        {
            fprintf(stderr, "pq_insert(): bad argument\n");
            exit(1);
        }

        pq->n_elem = 1;
        pq->buf[0] = proc;
        return;
    }

    if (pq->end == pq->head) {
        pq_overflow(pq);
    }

    i = pq->end;
    pq->end = (i + 1) % pq->bufsize;
    pq->n_elem++;
    pq->buf[i] = proc;
}

Process* pq_remove(ProcessQueue* pq){
    int i;
    Process* proc;

    if (!pq) {
        fprintf(stderr, "pq_insert(): bad argument\n");
        exit(1);
    }

    if (pq->n_elem == 0) {
        return NULL;
    }

    i = pq->head;
    proc = pq->buf[i];
    pq->buf[i] = NULL;
    i = (i + 1) % pq->bufsize;
    pq->head = i;
    pq->n_elem--;

    if (pq->n_elem * 2 <= pq->bufsize) {
        pq_underflow(pq);
    }

    return proc;
}

Process* pq_get_element(int index, ProcessQueue *pq) {
    int i;

    if (!pq) {
        fprintf(stderr, "pq_get_element(): bad argument\n");
        exit(1);
    }

    if (index >= pq->n_elem) {
        fprintf(stderr, "pq_get_element(): element out of bounds\n");
        exit(1);
    }

    i = (pq->head + index) % pq->bufsize;
    return pq->buf[i];
}


void pq_print(ProcessQueue *pq) {
    int i;
    char* out;
    Process* proc;

    if (!pq) {
        fprintf(stderr, "print_queue(): bad argument\n");
        exit(1);
    }

    for (i = 0; i < pq->n_elem; ++i) {
        proc = pq_get_element(i, pq);
        out = process_tostring(proc, 1024);
        fputs(out, stdout);
    }
}
