#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "list.h"

int main()
{
    struct graph *g = graph_init(1, 10);

    graph_print(g);
    
    graph_add_edge(g, 2, 0);
    graph_add_edge(g, 2, 4);
    graph_add_edge(g, 5, 6);
    graph_add_edge(g, 2, 6);
    graph_add_edge(g, 5, 6);

    graph_print(g);
/*
    g = graph_add_vertex(g);
    graph_print(g);
    graph_add_edge(g, 10, 6);
    graph_add_edge(g, 10, 4);

    g = graph_add_vertex(g);
    graph_add_edge(g, 11, 2);
    graph_add_edge(g, 11, 3);
    graph_print(g);

    g = graph_add_vertex(g);
    graph_add_edge(g, 12, 11);
    graph_add_edge(g, 12, 12);
    graph_print(g);

    graph_remove_edge(g, 12, 11);
    graph_remove_edge(g, 12, 12);
    graph_add_edge(g, 12, 3);
    graph_print(g);*/
/*
    struct graph *g = graph_load("../../files/data/test.gra");
    graph_print(g);

    graph_add_edge(g, 7, 6);
    graph_add_edge(g, 3, 4);

    graph_print(g);

    g = graph_add_vertex(g);
    graph_add_edge(g, 9, 3);

    graph_print(g);

    graph_save("../../files/data/test_save.gra", g);*/

    return 0;
}
