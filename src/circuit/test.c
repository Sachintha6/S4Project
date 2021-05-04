#include <stdlib.h>
#include <stdio.h>
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"
#include "dijkstra.h"

int main()
{
    struct mgraph *g = mgraph_init(1, 10);

    mgraph_print(g);
    
    mgraph_add_edge(g, 2, 0, -1);
    mgraph_add_edge(g, 2, 4, -1);
    mgraph_add_edge(g, 5, 6, -1);
    mgraph_add_edge(g, 2, 6, -1);
    mgraph_add_edge(g, 5, 6, -1);

    mgraph_print(g);

    g = mgraph_add_vertex(g, "New1", 13.0, 0.0);
    mgraph_print(g);
    mgraph_add_edge(g, 10, 6, -1);
    mgraph_add_edge(g, 10, 4, -1);

    g = mgraph_add_vertex(g, "New2", 18.0, 24.0);
    mgraph_add_edge(g, 11, 2, -1);
    mgraph_add_edge(g, 11, 3, -1);
    mgraph_print(g);

    mgraph_remove_vertex(g, 6);
    mgraph_remove_vertex(g, 5);
    mgraph_print(g);

    g = mgraph_add_vertex(g, "New3", 18.0, 24.0);
    mgraph_add_edge(g, 12, 2, -1);
    mgraph_add_edge(g, 12, 10, -1);
    mgraph_print(g);

    dijkstra(g, 0);

    return 0;
}