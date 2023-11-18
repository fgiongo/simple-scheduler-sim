#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_READY 0
#define PROCESS_RUNNING 1
#define PROCESS_BLOCKED 2

typedef struct _IoOp {
    int type; /* can be IO_DISK, IO_TAPE or IO_PRINT */
    int start_time;
    int running_time;
} IoOp;

typedef struct _Process {
    int pid;
    int creation_time;
    int cpu_time_max;
    int cpu_time;
    int io_status; /* can be either IO_DISK, IO_TAPE, IO_PRINT, IO_NONE */
    int time_until_ready;
    IoOp *io_ops;
} Process;

void process_init(Process*);

#endif
