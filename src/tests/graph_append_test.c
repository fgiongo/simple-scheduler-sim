#include "../modules/scheduler.h"

int main(void) {
    int i;
    Graph* graph;

    graph = graph_create();

    fprintf(stdout, "Graph G = {\n");
    for (i = 0; i < 100; ++i) {
        graph_append(i, i*i, graph);
        fprintf(stdout, "  (%d, %d)\n",
                graph_get_time(i, graph),
                graph_get_pid(i, graph));
    }
    fprintf(stdout, "}\n");

    return 0;
}
