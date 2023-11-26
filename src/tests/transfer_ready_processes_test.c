#include "../modules/scheduler.h"

ProcessQueue* trptest_gen_mock_io_queue(int n_proc, int io_type);
Process* trptest_get_next_zero_tur_process(int start_index, ProcessQueue* pq);
int trptest_min_max(int i, int min, int max);

int main(void) {
    ProcessQueue *queues[5];
    Process* proc;

    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = pq_create();
    queues[IO_DISK] = trptest_gen_mock_io_queue(100, IO_DISK);
    queues[IO_TAPE] = trptest_gen_mock_io_queue(100, IO_TAPE);
    queues[IO_PRINT] = trptest_gen_mock_io_queue(100, IO_PRINT);

    transfer_ready_processes(queues);
    proc = NULL;
    proc = trptest_get_next_zero_tur_process(0, queues[IO_DISK]);
    proc = trptest_get_next_zero_tur_process(0, queues[IO_TAPE]);
    proc = trptest_get_next_zero_tur_process(0, queues[IO_PRINT]);

    if (proc == NULL) {
        puts("Test passed =)");
        fprintf(stdout, "# of processes transfered to high priority queue: %d\n# of processes transfered to low priority queue: %d\n",
                queues[CPU_HIGH]->n_elem, queues[CPU_LOW]->n_elem);
    }
    else {
        fprintf(stdout, "Test failed, io_status: %d, tur: %d\n",
                proc->io_status, proc->time_until_ready);
    }

    return 0;
}

Process* trptest_get_next_zero_tur_process(int start_index, ProcessQueue* pq) {
    Process* proc;
    int i;

    for (i = start_index; i < pq->n_elem; ++i) {
        proc = pq_get_element(i, pq);
        if (proc->time_until_ready <= 0) {
            return proc;
        }
    }

    return NULL;
}

ProcessQueue* trptest_gen_mock_io_queue(int n_proc, int io_status) {
    ProcessQueue* queue;
    Process* proc;
    int i, io_max_length;

    switch (io_status) {
        case IO_DISK:
            io_max_length = IO_TIME_DISK;
            break;
        case IO_TAPE:
            io_max_length = IO_TIME_TAPE;
            break;
        case IO_PRINT:
            io_max_length = IO_TIME_PRINT;
            break;
        default:
            fprintf(stderr, "trp_test_gen_mock_io_queue(): invalid IO status\n");
            exit(1);
    }

    queue = pq_create();
    for (i = 0; i < n_proc; ++i) {
        proc = process_create(i+1, 0, 42);
        proc->io_status = io_status;
        proc->time_until_ready = trptest_min_max(i - n_proc / 3, 0, io_max_length);
        pq_insert(proc, queue);
    }

    return queue;
}

int trptest_min_max(int i, int min, int max) {
    if (i < min){
        return min;
    }

    if (i > max) {
        return max;
    }

    return i;
}
