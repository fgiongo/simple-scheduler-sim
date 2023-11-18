#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_READY 0
#define PROCESS_RUNNING 1
#define PROCESS_BLOCKED 2

typedef struct _Process {
    int pid;
    int creation_time;
    int cpu_time_max;
    int cpu_time;
    int io_status; /* can be either IO_DISK, IO_TAPE, IO_PRINT, IO_NONE */
    int time_until_ready;
    int* io_times;
    int* io_types;
    int io_n_elem;
} Process;

Process* process_create
(
        int, /* pid */
        int, /* creation_time: time of entry into simulation */
        int  /* cpu_time_max: amount of cpu time needed to finish */
);

void add_io_operation
(
        Process*, /* dest */
        int,      /* io operation time (in relation to process cpu time) */
        int       /* io type, can be IO_DISK, IO_TAPE, IO_PRINT */
);

#endif
