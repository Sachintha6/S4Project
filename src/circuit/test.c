#include <stdlib.h>
#include <stdio.h>
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"
#include "dijkstra.h"

int main()
{
    struct mgraph *g = mgraph_init(1, 9);
    
    mgraph_add_edge(g, 0, 1, -1);
    mgraph_add_edge(g, 1, 2, -1);
    mgraph_add_edge(g, 2, 3, -1);
    mgraph_add_edge(g, 2, 4, -1);
    mgraph_add_edge(g, 3, 4, -1);
    mgraph_add_edge(g, 2, 5, -1);
    mgraph_add_edge(g, 4, 5, -1);
    mgraph_add_edge(g, 5, 6, -1);
    mgraph_add_edge(g, 0, 6, -1);
    mgraph_add_edge(g, 3, 6, -1);
    mgraph_add_edge(g, 6, 4, -1);
    mgraph_add_edge(g, 1, 7, -1);
    mgraph_add_edge(g, 0, 7, -1);
    mgraph_add_edge(g, 7, 1, -1);
    
    mgraph_print(g);

    struct mgraph *ride = shortest_ride(g, 0, 4);

    printf("vvvvvvvvvvvv\nvvv RIDE vvv\nvvvvvvvvvvvv\n");

    mgraph_print(ride);

    return 0;
}