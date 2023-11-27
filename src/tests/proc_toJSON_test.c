#include "../modules/scheduler.h"

int main(void) {
    ProcessQueue* pq;
    Process* proc;
    char* str;
    int i, n_proc;

    n_proc = 5;
    pq = mock_input(n_proc, 10, 15);

    for (i = 0; i < n_proc; ++i) {
        proc = pq_get_element(i, pq);
        str = process_toJSON(proc);
        fputs(str, stdout);
        fputc('\n', stdout);
    }
    return 0;
}
