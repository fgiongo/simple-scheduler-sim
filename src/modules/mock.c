#include "scheduler.h"

ProcessQueue* mock_input
(int n_proc, int creation_time_limit, int cpu_time_limit)
{
    ProcessQueue *output;
    Process** proc_arr;
    int i;

    if (n_proc < 1) {
        fprintf(stderr, "mock_input(): bad argument\n");
        exit(1);
    }

    proc_arr = (Process**) calloc(n_proc, sizeof(Process*));
    if (!proc_arr) {
        fprintf(stderr, "mock_input(): bad alloc\n");
        exit(1);
    }

    output = pq_create();

    for (i = 0; i < n_proc; ++i) {
        proc_arr[i] = process_generate_mock(i, creation_time_limit,
                                             cpu_time_limit);
    }

    process_sort_by_creation_time(proc_arr, n_proc);

    for (i = 0; i < n_proc; ++i) {
        pq_insert(proc_arr[i], output);
    }

    free(proc_arr);

    return output;
}
