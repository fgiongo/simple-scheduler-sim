#include "../src/modules/scheduler.h"

int main(int argc, char** argv) {
    int n_proc;
    int creation_time_limit;
    int cpu_time_limit;
    ProcessQueue* pq;
    Process* proc;
    char* proc_str;
    int i;

    if (argc != 4) {
        fprintf(stderr, "Usage: json-gen [number of processes] [creation time limit] [cpu time limit]\n");
        exit(1);
    }

    n_proc = atoi(argv[1]);
    creation_time_limit = atoi(argv[2]);
    cpu_time_limit = atoi(argv[3]);

    if (n_proc < 1
        || creation_time_limit < 0
        || cpu_time_limit < 1)
    {
        fprintf(stderr, "json-gen: invalid argument(s)\n");
        exit(1);
    }

    pq = mock_input(n_proc, creation_time_limit, cpu_time_limit);
    fputs("[\n", stdout);
    for (i = 0; i < pq->n_elem - 1; ++i) {
        proc = pq_get_element(i, pq);
        proc_str = process_toJSON(proc);
        fputs(proc_str, stdout);
        fputs(",\n", stdout);
    }
    proc = pq_get_element(pq->n_elem - 1, pq);
    proc_str = process_toJSON(proc);
    fputs(proc_str, stdout);
    fputs("\n]\n", stdout);

    return 0;
}
