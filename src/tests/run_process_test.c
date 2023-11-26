#include "../modules/scheduler.h"

int main(void) {
    Graph* output_data;
    Process* proc;
    int time_elapsed;

    time_elapsed = 0;
    output_data = graph_create();

    /* Process with no IO requests that uses whole time slice */
    proc = process_create(1, 0, 2 + QUANTUM);
    run_process(proc, output_data, &time_elapsed);
    fprintf(stdout, "Quantum: %d\nfirst run data:\n", QUANTUM);
    graph_print(output_data);
    fputs(process_tostring(proc, 1024), stdout);
    fputc('\n', stdout);
    fprintf(stdout, "time at end of run: %d\n", time_elapsed);

    /* Process with no IO requests that finishes before end of time slice */
    proc->pid = 2;
    run_process(proc, output_data, &time_elapsed);
    fputs("second run data:\n", stdout);
    graph_print(output_data);
    fputs(process_tostring(proc, 1024), stdout);
    fputc('\n', stdout);
    fprintf(stdout, "time at end of run: %d\n", time_elapsed);

    /* Process with IO request */
    proc->pid = 3;
    proc->cpu_time_max = QUANTUM;
    proc->cpu_time = 0;
    add_io_operation(proc, 2, IO_DISK);
    run_process(proc, output_data, &time_elapsed);
    graph_print(output_data);
    fputs(process_tostring(proc, 1024), stdout);
    fputc('\n', stdout);
    fprintf(stdout, "time at end of run: %d\n", time_elapsed);


    return 0;
}
