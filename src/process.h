#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_READY 0
#define PROCESS_RUNNING 1
#define PROCESS_BLOCKED 2

#define IO_DISK 0
#define IO_TAPE 1
#define IO_PRINT 2

typedef struct _IoOp {
    int type; /* can be IO_DISK, IO_TAPE or IO_PRINT */
    int start_time;
    int running_time;
} IoOp;

typedef struct _Process {
    int pid;
    int status; /* can be either PROCESS_READY, PROCESS_RUNNING,
                   PROCESS_BLOCKED, PROCESS_RUNNING_SUSPENDED,
                   PROCESS_BLOCKED_SUSPENDED */
    int start_time;
    int running_time;
    int cpu_time;
    int time_until_ready;
    IoOp *io_ops;
} Process;

void process_init(Process*);

#endif
