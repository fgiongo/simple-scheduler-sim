#ifndef QUEUE_H
#define QUEUE_H
#include "process.h"

typedef struct _ProcessQueue {
    Process **buf;
    int bufsize;
    int head;
    int end;
} ProcessQueue;

#endif
