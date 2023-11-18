#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

Process* process_create
(
        int pid,
        int creation_time,
        int cpu_time_max
)
{
    Process *p = (Process *) malloc(sizeof(Process));
    if (!p){
        fprintf(stderr, "create_process: could not create new process\n");
        exit(1);
    }

    p->pid = pid;
    p->creation_time = creation_time;
    p->cpu_time_max = cpu_time_max;
    p->cpu_time = 0;
    p->io_status = IO_NONE;
    p->time_until_ready = 0;
    p->io_times = NULL;
    p->io_types = NULL;
    p->io_n_elem = 0;

    return p;
}

void add_io_operation
(
        Process* proc,
        int io_time,
        int io_type
)
{
    int* new_io_times;
    int* new_io_types;

    if (proc->io_n_elem == 0) {
        new_io_times = (int*) malloc(sizeof(int));
        new_io_types = (int*) malloc(sizeof(int));
        if (!new_io_times || !new_io_types) {
            fprintf(stdout, "add_io_operation(): bad alloc\n");
            exit(1);
        }

        proc->io_times = new_io_times;
        proc->io_types = new_io_types;
        proc->io_n_elem = 1;

        proc->io_times[0] = io_time;
        proc->io_types[0] = io_type;
    }
    else {
        new_io_times = (int*) malloc(sizeof(int) * proc->io_n_elem + 1);
        new_io_types = (int*) malloc(sizeof(int) * proc->io_n_elem + 1);
        if (!new_io_times || !new_io_types) {
            fprintf(stdout, "add_io_operation(): bad alloc\n");
            exit(1);
        }

        memcpy(new_io_times, proc->io_times, proc->io_n_elem * sizeof(int));
        memcpy(new_io_types, proc->io_types, proc->io_n_elem * sizeof(int));
        proc->io_n_elem++;
        new_io_times[proc->io_n_elem - 1] = io_time;
        new_io_types[proc->io_n_elem - 1] = io_type;
        free(proc->io_times);
        free(proc->io_types);
        proc->io_times = new_io_times;
        proc->io_types = new_io_types;
    }
}

