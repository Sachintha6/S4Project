#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "list.h"

struct graph *graph_init(int directed, int order)
{
    struct graph gp = {0, 0, NULL};
    struct graph *g = &gp;

    g->directed = directed;
    g->order = order;
    g->adjlists = malloc(order * sizeof(struct list));

    return g;
}

void graph_print(struct graph *g)
{
    printf("-- Graph of %d vertex\n", g->order);
}

