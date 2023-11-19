#include "../scheduler.h"

int main(void) {

    char *proc_desc;
    ProcessQueue* pq;
    Process* proc;
    int n_proc, i;

    srand((unsigned) time(NULL));

    n_proc = 5;
    pq = mock_input(n_proc, 10, 20);

    for (i = 0; i < n_proc; ++i) {
        proc = pq_get_element(i, pq);
        proc_desc = process_tostring(proc, 512);
        fprintf(stdout, "%s", proc_desc);
    }

    return 0;
}
