#include "scheduler.h"


void add_new_processes_test_setup
(ProcessQueue **queues, ProcessQueue *new_processes);

int run_add_new_processes_tests
(ProcessQueue **queues, ProcessQueue *new_processes);

int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes);

int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes);

int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes);

int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes);

int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes);


int main(void) {
    ProcessQueue* new_processes;
    ProcessQueue* queues[5];

    add_new_processes_test_setup(queues,
                                 new_processes);

    run_add_new_processes_tests(ProcessQueue **queues,
                                ProcessQueue *new_processes);

    return 0;
}


void add_new_processes_test_setup
(ProcessQueue **queues, ProcessQueue *new_processes)
{

    new_processes = pq_create();
    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = NULL;
    queues[IO_DISK] = NULL;
    queues[IO_TAPE] = NULL;
    queues[IO_PRINT] = NULL;

    pq_insert(p1, new_processes);
    pq_insert(p2, new_processes);
    pq_insert(p3, new_processes);
}


int run_add_new_processes_tests
(ProcessQueue **queues, ProcessQueue *new_processes)
{
    int results[5];
    int final_result;

    results[0] = add_new_processes_test1(queues, new_processes, time_elapsed);
    results[1] = add_new_processes_test2(queues, new_processes, time_elapsed);
    results[2] = add_new_processes_test3(queues, new_processes, time_elapsed);
    results[3] = add_new_processes_test4(queues, new_processes, time_elapsed);
    results[4] = add_new_processes_test5(queues, new_processes, time_elapsed);

    final_result = 1;
    for (i = 0; i < 5, ++i) {
        if (!results[i]) {
            final_result = 0;
        }
    }

    return final_result;
}


/* Test 1: no processes in new_processes queue */
int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes)
{
}


/* Test 2: 3 processes in new_process queue, but none have started yet */
int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes)
{
}


/* Test 3: 3 processes in new_process queue, 1 has started, 2 have not */
int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes)
{
}


/* Test 4: 3 processes in new_process queue, 2 have started, 1 has not */
int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes)
{
}


/* Test 5: 3 processes in new_process queue, all have started */
int add_new_processes_test_1
(ProcessQueue **queues, ProcessQueue *new_processes)
{
}
