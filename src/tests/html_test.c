#include "../modules/scheduler.h"

int main(void){

    Graph* grafico;

    grafico = graph_create();
    graph_append(0, 1, grafico);
    graph_append(5, 2, grafico);
    graph_append(10, 3, grafico);

    output_graph(grafico);

    return 0;
}