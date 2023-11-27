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


void process_sort_by_creation_time(Process** arr, int n_elem) {
    int ordered, i;
    Process* tmp;

    for (ordered = 0;
         ordered < n_elem;
         ++ordered)
    {
        for (i = n_elem - 1;
             i > ordered;
             --i)
        {
            if (arr[i]->creation_time
                < arr[i-1]->creation_time)
            {
                tmp = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}


int process_has_io_at_time(Process* proc, int t) {
    int result, i;

    if (!proc) {
        fprintf(stderr, "process_has_io_at_time(): bad argument\n");
        exit(1);
    }

    result = 0;
    for (i = 0; i < proc->io_n_elem; ++i) {
        if (proc->io_times[i] == t) {
            result = 1;
        }
    }
    
    return result;
}


int process_get_io_type_at_time
(
        Process* proc, /* Process to search for io_type */
        int time,      /* time for which to search */
        int* io_index  /* output: io_index at time */
)
{
    int i, index;

    if (!proc) {
        fprintf(stderr, "process_get_io_type_at_time(): bad argument\n");
        exit(1);
    }

    index = -1;
    for (i = 0; i < proc->io_n_elem; ++i) {
        if (proc->io_times[i] == time) {
            index = i;
        }
    }

    if (index == -1) {
        return 0;
    }

    *io_index = index;
    return 1;
}


Process* process_generate_mock
(int pid, int creation_time_limit, int cpu_time_limit)
{
    Process* proc;
    int creation_time, cpu_time_max;
    int io_n_elem, io_time, io_type;
    int i;

    creation_time = rand() % (creation_time_limit + 1);
    cpu_time_max = (rand() % cpu_time_limit + 1);
    if (cpu_time_max / 2 != 0) {
        io_n_elem = rand() % (cpu_time_max / 2);
    }
    else {
        io_n_elem = 0;
    }
    proc = process_create(pid, creation_time, cpu_time_max);

    i = 0;
    while (i < io_n_elem) {
        io_type = rand() % 3;
        switch (io_type) {
            case 0:
                io_type = IO_DISK;
                break;
            case 1:
                io_type = IO_TAPE;
                break;
            case 2:
                io_type = IO_PRINT;
                break;
        }

        do {
            io_time = rand() % (proc->cpu_time_max + 1);
        } while (process_has_io_at_time(proc, io_time));

        add_io_operation(proc, io_time, io_type);
        ++i;
    }

    return proc;
}

char* process_tostring(Process* p, int bufsize) {
    char* out;
    char value[32];
    int i, j, k, io_status;

    if (!p || bufsize < 512) {
        fprintf(stdout, "process_tostring(): bad argument\n");
        exit(1);
    }

    bufsize = 512;
    out = (char*) calloc(bufsize, sizeof(char));
    if (!out) {
        fprintf(stdout, "process_tostring(): bad alloc\n");
        exit(1);
    }

    i = 0;
    strcpy(&out[i], "Process:\nPID: ");
    i += 14;
    j = sprintf(value, "%d\n", p->pid);
    strcpy(&out[i], value);
    i += j;

    strcpy(&out[i], "created at time : ");
    i += 18;
    j = sprintf(value, "%d\n", p->creation_time);
    strcpy(&out[i], value);
    i += j;

    strcpy(&out[i], "total cpu time needed to complete: ");
    i += 35;
    j = sprintf(value, "%d\n", p->cpu_time_max);
    strcpy(&out[i], value);
    i += j;

    strcpy(&out[i], "cpu time used so far: ");
    i += 22;
    j = sprintf(value, "%d\n", p->cpu_time);
    strcpy(&out[i], value);
    i += j;

    strcpy(&out[i], "current i/o request status: ");
    i += 28;

    io_status = p->io_status;
    switch (io_status){
        case IO_NONE:
            strcpy(&out[i], "none\n");
            i += 5;
            break;
        case IO_DISK:
            strcpy(&out[i], "disk\n");
            i += 5;
            break;
        case IO_TAPE:
            strcpy(&out[i], "tape\n");
            i += 5;
            break;
        case IO_PRINT:
            strcpy(&out[i], "print\n");
            i += 6;
            break;
        default:
            strcpy(&out[i], "undefined\n");
            i += 10;
    }

    if (io_status != IO_NONE) {
        strcpy(&out[i], "time until i/o is finished: ");
        i += 28;
        j = sprintf(value, "%d\n", p->time_until_ready);
        strcpy(&out[i], value);
        i += j;
    }

    if (p->io_n_elem > 0) {
        strcpy(&out[i], "upcoming i/o requests: \n");
        i += 24;

        for (k = 0;
             k < p->io_n_elem && i < bufsize - 64;
             ++k)
        {
            strcpy(&out[i], "request:\ntime: ");
            i += 15;
            j = sprintf(value, "%d\n", p->io_times[k]);
            strcpy(&out[i], value);
            i += j;

            strcpy(&out[i], "type: ");
            i += 6;
            io_status = p->io_types[k];
            switch (io_status){
                case IO_DISK:
                    strcpy(&out[i], "disk\n");
                    i += 5;
                    break;
                case IO_TAPE:
                    strcpy(&out[i], "tape\n");
                    i += 5;
                    break;
                case IO_PRINT:
                    strcpy(&out[i], "print\n");
                    i += 6;
                    break;
                default:
                    strcpy(&out[i], "undefined\n");
                    i += 10;
            }
        }

        strcpy(&out[i], "total upcoming i/o requests: ");
        i += 29;
        j = sprintf(value, "%d\n", p->io_n_elem);
        strcpy(&out[i], value);
        i += j;
    }

    strcpy(&out[i], "\n");
    i += 1;

    return out;
}


void process_free(Process* p) {
    if (!p) {
        fprintf(stderr, "process_free(): bad argument\n");
        exit(1);
    }

    if (p->io_n_elem > 0) {
        free(p->io_times);
        free(p->io_types);
    }

    free(p);
}

char* process_toJSON(Process* p) {
    char *out, *tmp;
    int size, i;

    out = (char*) malloc(sizeof(char) * 1024);
    if (!out) {
        fprintf(stderr, "process_toJSON(): bad alloc\n");
        exit(1);
    }

    size = 0;
    size += sprintf(out + size, "{\n\"pid\": ");
    size += sprintf(out + size, "%d,\n", p->pid);
    size += sprintf(out + size, "\"creation_time\": ");
    size += sprintf(out + size, "%d,\n", p->creation_time);
    size += sprintf(out + size, "\"cpu_time_max\": ");
    size += sprintf(out + size, "%d,\n", p->cpu_time_max);
    size += sprintf(out + size, "\"io_times\": [");
    for (i = 0; i < p->io_n_elem; i++) {
        size += sprintf(out + size, "%d, ", p->io_times[i]);
    }
    if (p->io_n_elem > 0){
        size -= 2;
    }
    size += sprintf(out + size, "],\n");
    size += sprintf(out + size, "\"io_types\": [");
    for (i = 0; i < p->io_n_elem; i++) {
        switch (p->io_types[i]){
            case IO_DISK: 
                size += sprintf(out + size, "\"DISK\", ");
                break;
            case IO_TAPE:
                size += sprintf(out + size, "\"TAPE\", ");
                break;
            case IO_PRINT:
                size += sprintf(out + size, "\"PRINT\", ");
                break;
            default:
                size += sprintf(out + size, "\"UNDEFINED\", ");
                break;
        }
    }
    if (p->io_n_elem > 0){
        size -= 2;
    }
    size += sprintf(out + size, "]\n}");
    out[size] = '\0';
    size++;

    tmp = (char*) realloc(out, sizeof(char) * size);
    if (!tmp) {
        fprintf(stderr, "process_toJSON(): bad alloc\n");
        exit(1);
    }
    if (out != tmp) {
        free(out);
    }
    out = tmp;

    return out;
}
