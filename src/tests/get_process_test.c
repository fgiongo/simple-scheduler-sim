#include "../modules/scheduler.h"

int main (void){
    Process *p;
    Process *process1;
    Process *process2;
    Process *process3;
    Process *process4;
    ProcessQueue *queues[5];

    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = pq_create();
    queues[IO_DISK] = pq_create();
    queues[IO_TAPE] = pq_create();
    queues[IO_PRINT] = pq_create();
    
    process1 = process_create(1, 5, 10);
    process2 = process_create(2, 1, 8);
    process3 = process_create(3, 2, 12);
    process4 = process_create(4, 3, 15);

    pq_insert(process1, queues[CPU_HIGH]);
    pq_insert(process2, queues[CPU_HIGH]);
    pq_insert(process3, queues[CPU_LOW]);
    pq_insert(process4, queues[CPU_LOW]);


    p = get_next_process(queues);
    while(p != NULL){ 
        printf("pid: %d\n", p -> pid);
        p = get_next_process(queues);
    }


    pq_insert(process3, queues[CPU_HIGH]);
    pq_insert(process4, queues[CPU_HIGH]);
    pq_insert(process1, queues[CPU_LOW]);
    pq_insert(process2, queues[CPU_LOW]);

    printf("\n\n");

    p = get_next_process(queues);
    while(p != NULL){ 
        printf("pid: %d\n", p -> pid);
        p = get_next_process(queues);
    }

    printf("\n\n");

    /*pq_insert(process3, queues[CPU_HIGH]);
    pq_insert(process4, queues[CPU_HIGH]);*/
    pq_insert(process1, queues[CPU_LOW]);
    pq_insert(process2, queues[CPU_LOW]);

    p = get_next_process(queues);
    while(p != NULL){ 
        printf("pid: %d\n", p -> pid);
        p = get_next_process(queues);
    }

    pq_insert(process3, queues[CPU_HIGH]);
    pq_insert(process4, queues[CPU_HIGH]);
    /*pq_insert(process1, queues[CPU_LOW]);
    pq_insert(process2, queues[CPU_LOW]);*/

    printf("\n\n");

    p = get_next_process(queues);
    while(p != NULL){ 
        printf("pid: %d\n", p -> pid);
        p = get_next_process(queues);
    }

    return 0;
}