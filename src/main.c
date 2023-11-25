#include <stdio.h>
#include <stdlib.h>
#include "./modules/scheduler.h"

int main(void){
    ProcessQueue *queues[5];
    ProcessQueue *new_processes;
    Process* running_process;
    Graph *run_data;
    Graph *output_data;
    int i;
    int time_elapsed;
    int latest_run_duration;

    run_data = graph_create();
    output_data = graph_create();

    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = pq_create();
    queues[IO_DISK] = pq_create();
    queues[IO_TAPE] = pq_create();
    queues[IO_PRINT] = pq_create();

    new_processes = parse_JSON();
    latest_run_duration = 0;
    time_elapsed = 0;

    while (1) {

        if (new_processes->n_elem > 0) {
            add_new_processes(new_processes, queues, time_elapsed);
        }
        else if (queues[CPU_HIGH]->n_elem == 0
                 && queues[CPU_LOW]->n_elem == 0
                 && queues[IO_DISK]->n_elem == 0
                 && queues[IO_TAPE]->n_elem == 0
                 && queues[IO_PRINT]->n_elem == 0)
        {
            break;
        }

        if (latest_run_duration > 0) {
            update_io_wait_time(queues, latest_run_duration);
            transfer_ready_processes(queues);
        }

        running_process = get_next_process(queues);

        if (!running_process) {
            latest_run_duration = 1;
            time_elapsed++;
            continue;
        }

        latest_run_duration = time_elapsed;
        run_process(running_process, run_data, &time_elapsed);
        latest_run_duration = time_elapsed - latest_run_duration;

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
