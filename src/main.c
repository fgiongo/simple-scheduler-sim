#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scheduler.h"


int main(void){
    global_pid = 0;
    global_queues = (ProcessQueue *) malloc(sizeof(ProcessQueue) * 3);
    if (!global_queues){
        fprintf(stderr, "main(): could not initialize global queues array\n");
        exit(1);
    }

    process_queue_init(&global_queues[0]);
    process_queue_init(&global_queues[1]);
    process_queue_init(&global_queues[2]);

    create_process();
    global_n_processes = 1;

    srand((unsigned) time(NULL));

    /* main loop */
    while(1){
        /* small random chance of spawning new process at every iteration */
        if ((rand() % 10) == 0 && global_n_processes < PROCESS_MAX){
            create_process();
            global_n_processes++;
        }
        handle_next_instruction();
    }

    return 0;
}

void handle_next_instruction(void){
    Process *p = fetch_next_process();
    if (p->pc == (p->n_instructions - 1)){
        process_destroy(p);
    }
    p->pc += 1;
}
