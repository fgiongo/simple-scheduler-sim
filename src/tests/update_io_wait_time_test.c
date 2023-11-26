#include "../modules/scheduler.h"

int update_io_wait_time_test_queue(ProcessQueue* pq);
void setup_queue_for_update_io_wait_time_test (ProcessQueue* pq);

int main(void) {
    ProcessQueue *queues[5];
    int time_since_last_update;

    srand((unsigned) time(NULL));

    queues[IO_DISK] = mock_input(10, 0, 100);
    queues[IO_TAPE] = mock_input(10, 0, 100);
    queues[IO_PRINT] = mock_input(10, 0, 100);

    time_since_last_update = IO_TIME_TAPE + 1;

    setup_queue_for_update_io_wait_time_test(queues[IO_DISK]);
    setup_queue_for_update_io_wait_time_test(queues[IO_TAPE]);
    setup_queue_for_update_io_wait_time_test(queues[IO_PRINT]);

    time_since_last_update = IO_TIME_TAPE + 1;
    update_io_wait_time(queues, time_since_last_update);
    pq_print(queues[IO_DISK]);
    pq_print(queues[IO_TAPE]);
    pq_print(queues[IO_PRINT]);

    if (update_io_wait_time_test_queue(queues[IO_DISK])
        && update_io_wait_time_test_queue(queues[IO_TAPE])
        && update_io_wait_time_test_queue(queues[IO_PRINT]))
    {
        fprintf(stdout, "test passed =)\n");
    }
    else
    {
        fprintf(stdout, "test failed =(\n");
    }

    return 0;
}

int update_io_wait_time_test_queue(ProcessQueue* pq) {
    int i;
    Process* proc;

    for (i = 0; i < pq->n_elem; ++i){
        proc = pq_get_element(i, pq);
        if ((proc->io_status == IO_DISK || proc->io_status == IO_TAPE)
            && proc->time_until_ready != 0)
        {
            return 0;
        }
    }

    return 1;
}


void setup_queue_for_update_io_wait_time_test
(ProcessQueue* pq)
{
    int i, t, status;
    Process* proc;

    for (i = 0; i < pq->n_elem; ++i) {
        t = rand() % (IO_TIME_PRINT + 1);

        if (t > IO_TIME_TAPE) {
            status = IO_PRINT;
        }
        else if (t > IO_TIME_DISK) {
            status = IO_TAPE;
        }
        else {
            status = IO_DISK;
        }

        proc = pq_get_element(i, pq);
        proc->io_status = status;
        proc->time_until_ready = t;
    }
}
