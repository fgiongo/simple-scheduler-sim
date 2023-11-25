#include "../modules/scheduler.h"

int main(void) {
    ProcessQueue *queues[5];
    ProcessQueue *new_processes;
    Process* proc;
    Graph *run_data;
    Graph *output_data;
    int i, n_processes;
    int time_elapsed;
    int latest_run_duration;
    char *output;

    run_data = graph_create();
    output_data = graph_create();

    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = pq_create();
    queues[IO_DISK] = pq_create();
    queues[IO_TAPE] = pq_create();
    queues[IO_PRINT] = pq_create();


    n_processes = 5;
    new_processes = mock_input(n_processes, 10, 20);
    latest_run_duration = 0;
    time_elapsed = 10;

    if (new_processes->n_elem > 0) {
        add_new_processes(new_processes, queues, time_elapsed);
    }

    for (i = 0; i < n_processes; ++i) {
        proc = pq_get_element(i, queues[CPU_HIGH]);
        output = process_tostring(proc, 1024);
        fprintf(stdout, output);
    }

    return 0;
}
