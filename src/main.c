#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scheduler.h"


int main(void){
    Process* process_arr;
    Process* running;
    int quantum, interval;

    /* TODO: initialize all 3 queues*/
    init_queues();

    /* TODO: parse JSON from stdin */
    process_arr = parse_JSON();

    quantum = 4;
    interval = 20;
    running = NULL;

    /* main loop */
    while (1) {

        /* TODO: at every set interval, recalculate priorities based on CPU utilization */
        if (time % interval == 0) {
            update_priorities();
        }

        /* TODO: add new processes to priority queues */
        add_new_processes(process_arr);

        /* TODO: transfer ready processes from IO queues to CPU queues */
        transfer_ready_processes();

        /* TODO: if there is no running process and all queues are empty, we are done */
        if (!running && all_queues_are_empty()) {
            break;
        }

        /* TODO: otherwise if no process is running, select new process for execution,
         * remove from queue */
        if (!running) {
            running = get_process_from_queues();
        }

        /* TODO: check if process is over */
        if (is_finished(running)) {

            /* TODO: if it is, kill its children (remove from queues) */
            kill_all_children(running);

            /* TODO: then kill it (it is enough to not put it back in any queue) */
            kill(running);

            running = NULL;
            continue;
        }

        /* TODO: check if process nees IO at current time */
        if (needs_io(running)) {

            /* TODO: set status to blocked, set IO timeout and transfer to correct IO queue */
            block_process(running);
            
            running = NULL;
            continue;
        }

        /* TODO: check if process quantum is over */
        if (quantum_timed_out(running)) {

            /* TODO: return process to its priority queue */
            return_to_queue(running);

            running = NULL;
            continue;
        }

        /* TODO: advance time unit and update process */
        run_process(running);

        /* TODO: generate console output and graphical coordinates about process that was ran */
        generate_output(running);

    }

    return 0;
}
