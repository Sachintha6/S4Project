#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "list.h"

struct graph* graph_init(int directed, int order)
{
    struct graph *g = (struct graph*)malloc(sizeof(struct graph) + sizeof(struct list*) * order);
    g->directed = directed;
    g->order = order;

    for (int i = 0; i < order; i++)
    {
        g->adjlists[i] = (struct list*)malloc(sizeof(struct list));
        list_init(g->adjlists[i]);
        list_push(g->adjlists[i], i);
    }
    return g;
}

void graph_print(struct graph *g)
{
    // Header
    printf(" -- Print Graph --\n");
    printf(" | Vertex: %5d |\n", g->order);
    if (g->directed == 1)
        printf(" | Directed: Yes |\n");
    else
        printf(" | Directed:  No |\n");
    printf(" -----------------\n");

    // Body
    for (int i = 0; i < g->order; i++)
    {
        printf("%d\n", g->adjlists[i]->next->data);
    }
}

