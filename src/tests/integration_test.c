#include "../modules/scheduler.h"

/* integration: limit to avoid infinite loop */
#define MAX_ITER 100

int main(void){
    ProcessQueue *queues[5];
    ProcessQueue *new_processes;
    Process* running_process;
    Graph *output_data;
    int time_elapsed;
    int latest_run_duration;
    
    /* integration: limit to avoid infinite loop */
    int iter;
    iter = 1;


    output_data = graph_create();

    queues[CPU_HIGH] = pq_create();
    queues[CPU_LOW] = pq_create();
    queues[IO_DISK] = pq_create();
    queues[IO_TAPE] = pq_create();
    queues[IO_PRINT] = pq_create();

    new_processes = parse_JSON();
    /*
    new_processes = mock_input(5, 10, 10);
    */

    /* integration: print input */
    fprintf(stdout, "Input processes:\n");
    pq_print(new_processes);

    latest_run_duration = 0;
    time_elapsed = 0;

    while (iter <= MAX_ITER) {

        /* integration: print elapsed_time */
        fprintf(stdout, "\n\n ******** Main loop iteration: time elapsed: %d ********\n\n",
                time_elapsed);

        /* integration: print queues */
        fprintf(stdout, "Queues status:\n");
        fprintf(stdout, "New processes queue:\n");
        pq_print(new_processes);
        fprintf(stdout, "\nCPU HIGH queue:\n");
        pq_print(queues[CPU_HIGH]);
        fprintf(stdout, "\nCPU LOW queue:\n");
        pq_print(queues[CPU_LOW]);
        fprintf(stdout, "\nIO DISK queue:\n");
        pq_print(queues[IO_DISK]);
        fprintf(stdout, "\nIO TAPE queue:\n");
        pq_print(queues[IO_TAPE]);
        fprintf(stdout, "\nIO PRINT queue:\n");
        pq_print(queues[IO_PRINT]);


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
            /* integration */
            fprintf(stdout, "\nCPU idling!:\n");

            latest_run_duration = 1;
            time_elapsed++;
            continue;
        }

        latest_run_duration = time_elapsed;
        run_process(running_process, output_data, &time_elapsed);
        latest_run_duration = time_elapsed - latest_run_duration;

        /* integration */
        fprintf(stdout, "\nCPU running process (PID: %d):\n", 
                running_process->pid);

        if (running_process->cpu_time < running_process->cpu_time_max) {
            requeue_process(running_process, queues);
        }

        /* integration: limit to avoid infinite loop */
        iter++;
    }

    output_graph(output_data);
    return 0;
}
