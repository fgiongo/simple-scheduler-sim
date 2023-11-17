#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"


int main(void){
    Process* process_arr;
    Process* running_process;
    Graph *run_data;
    Graph *output;
    int i;

    init_global_queues();
    graph_init(output);
    process_arr = parse_JSON();
    global_time = 0;
    run_data = NULL;

    while (1) {

        add_new_processes(process_arr);
        update_queues();
        running_process = get_next_process();

        if (!running_process) {
            break;
        }

        run_data = run_process(running_process);

        if (run_data) {
            for (i = 0; i < run_data->size; ++i) {
                graph_append(run_data->values[i], output);
            }
        }

        if (running_process->cpu_time < running_process->running_time) {
            requeue_process(running_process);
        }
    }

    output_graph(output);
    return 0;
}
