#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_MAX  10

#define PROCESS_READY 0
#define PROCESS_RUNNING 1
#define PROCESS_BLOCKED 2
#define PROCESS_RUNNING_SUSPENDED 3
#define PROCESS_BLOCKED_SUSPENDED 3

#define PROCESS_IO_BOUNDED 0
#define PROCESS_CPU_BOUNDED 1

typedef struct _Process {
    int pid;
    int status; /* can be either PROCESS_READY, PROCESS_RUNNING,
                   PROCESS_BLOCKED, PROCESS_RUNNING_SUSPENDED,
                   PROCESS_BLOCKED_SUSPENDED */
    int priority;
    int nice;
    int *instructions;
    int n_instructions;
    int pc;
} Process;

void create_process(void);
void process_init(Process *p);
Process* fetch_next_process(void);
void process_destroy(Process *p);

#endif
