#include "../modules/scheduler.h"

int main (void){
    Process *process1;
    Process *process2;
    Process *process3;
    Process *process4;
    Process *process5;
    Process *process6;
    ProcessQueue *queues[5];
    int i;

    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = pq_create();
    queues[IO_DISK] = pq_create();
    queues[IO_TAPE] = pq_create();
    queues[IO_PRINT] = pq_create();
    
    process1 = process_create(1, 5, 10);
    process2 = process_create(2, 1, 8);
    process3 = process_create(3, 2, 12);
    process4 = process_create(4, 3, 15);
    process5 = process_create(5, 6, 16);
    process6 = process_create(6, 7, 16);


    process1 -> io_status = IO_NONE;
    process2 -> io_status = IO_DISK;
    process3 -> io_status = IO_TAPE;
    process4 -> io_status = IO_PRINT;
    process5 -> io_status = IO_TAPE;
    process6 -> io_status = 8;

    requeue_process(process1, queues);
    requeue_process(process2, queues);
    requeue_process(process3, queues);
    requeue_process(process4, queues);
    requeue_process(process5, queues);


    printf("CPU_LOW\n");
    for (i = 0; i < queues[CPU_LOW] -> n_elem; i++){
        printf("pid: %d\n", queues[CPU_LOW] -> buf[i] -> pid);
    }
    printf("\n");


    printf("IO_DISK\n");
    for (i = 0; i < queues[IO_DISK] -> n_elem; i++){
        printf("pid: %d\n", queues[IO_DISK] -> buf[i] -> pid);
    }
    printf("\n");


    printf("IO_TAPE\n");
    for (i = 0; i < queues[IO_TAPE] -> n_elem; i++){
        printf("pid: %d\n", queues[IO_TAPE] -> buf[i] -> pid);
    }
    printf("\n");


    printf("IO_PRINT\n");
    for (i = 0; i < queues[IO_PRINT] -> n_elem; i++){
        printf("pid: %d\n", queues[IO_PRINT] -> buf[i] -> pid);
    }
    printf("\n");


    requeue_process(process6, queues);
    return 0;
}