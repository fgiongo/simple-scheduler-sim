#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_READY 0
#define PROCESS_RUNNING 1
#define PROCESS_BLOCKED 2

typedef struct _Process {
    int pid;
    int creation_time;
    int cpu_time_max; /* maximum number of time units spent running
                         cannot be zero! */
    int cpu_time; /* number of time units spent running so far */
    int io_status; /* can be either IO_DISK, IO_TAPE, IO_PRINT, IO_NONE */
    int time_until_ready; /* time units left when waiting in IO queues */
    int* io_times; /* cpu_time's when process will request IO */
    int* io_types; /* type of IO requested at each io_time 
                      number of elements of this array must equal the
                      number of elememnts of io_times! */
    int io_n_elem; /* number of elements in arrays io_times, io_types */
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

void process_sort_by_creation_time
(
        Process**,
        int n_elem
);

int process_has_io_at_time
(
        Process* proc, /* Process to search for io_time */
        int t          /* time for which to search */
);

Process* process_generate_mock
(
        int pid,
        int creation_time_limit,
        int cpu_time_limit
);

char* process_tostring(
        Process*, /* process to be made to string */
        int       /* size of string buffer */
);

#endif
