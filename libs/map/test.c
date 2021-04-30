#include <stdlib.h>
#include <stdio.h>
#include "mapGraph.h"
#include "list.h"

int main()
{
    struct mgraph *g = mgraph_init(1, 10);

    mgraph_print(g);
    
    mgraph_add_edge(g, 2, 0);
    mgraph_add_edge(g, 2, 4);
    mgraph_add_edge(g, 5, 6);
    mgraph_add_edge(g, 2, 6);
    mgraph_add_edge(g, 5, 6);

    mgraph_print(g);

    g = mgraph_add_vertex(g, "New1", 13.0, 0.0);
    mgraph_print(g);
    mgraph_add_edge(g, 10, 6);
    mgraph_add_edge(g, 10, 4);

    g = mgraph_add_vertex(g, "New2", 18.0, 24.0);
    mgraph_add_edge(g, 11, 2);
    mgraph_add_edge(g, 11, 3);
    mgraph_print(g);

    mgraph_remove_vertex(g, 6);
    mgraph_remove_vertex(g, 5);
    mgraph_print(g);

    g = mgraph_add_vertex(g, "New3", 18.0, 24.0);
    mgraph_add_edge(g, 12, 2);
    mgraph_add_edge(g, 12, 10);
    mgraph_print(g);

    /*g = mgraph_add_vertex(g);
    mgraph_add_edge(g, 12, 11);
    mgraph_add_edge(g, 12, 12);
    mgraph_print(g);

    mgraph_remove_edge(g, 12, 11);
    mgraph_remove_edge(g, 12, 12);
    mgraph_add_edge(g, 12, 3);
    mgraph_print(g);*/

    /*struct graph *g = graph_load("../../files/data/test.gra");
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