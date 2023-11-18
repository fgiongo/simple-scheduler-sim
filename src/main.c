#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

int main(void){
    ProcessQueue *queues[5];
    ProcessQueue *new_processes;
    Process* running_process;
    Graph *run_data;
    Graph *output_data;
    int i;
    int time_elapsed;
    int time_since_last_update;

    run_data = graph_create();
    output_data = graph_create();

    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = pq_create();
    queues[IO_DISK] = pq_create();
    queues[IO_TAPE] = pq_create();
    queues[IO_PRINT] = pq_create();

    new_processes = parse_JSON();
    time_elapsed = 0;

    while (1) {


        if (new_processes->n_elem > 0) {
            add_new_processes(new_processes, queues, time_elapsed);
        }

        time_since_last_update = run_data->n_elem;

        if (time_since_last_update > 0) {
            update_io_wait_time(queues, time_since_last_update);
            transfer_ready_processes(queues);
        }

        running_process = get_next_process(queues);

        if (!running_process) {
            break;
        }

        run_process(running_process, run_data, &time_elapsed);

        for (i = 0; i < run_data->n_elem; ++i) {
            graph_append(run_data->time[i],
                         run_data->pid[i],
                         output_data);
        }

        if (running_process->cpu_time < running_process->cpu_time_max) {
            requeue_process(running_process, queues);
        }
    }

    output_graph(output_data);
    return 0;
}
