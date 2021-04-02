#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "graph.h"
#include "list.h"

struct graph *graph_init(int directed, int order)
{
    struct graph *g = (struct graph*)malloc(sizeof(struct graph) + sizeof(struct list*) * order);
    g->directed = directed;
    g->order = order;

    for (int i = 0; i < order; i++)
    {
        g->adjlists[i] = (struct list*)malloc(sizeof(struct list));
        list_init(g->adjlists[i]);
        //list_push(g->adjlists[i], i);
    }
    return g;
}

void graph_add_edge(struct graph *g, int src, int dst)
{
    if (src < 0 || src >= g->order)
    {
        err(EXIT_FAILURE, "Invalid src index");
    }

    if (dst < 0 || dst >= g->order)
    {
        err(EXIT_FAILURE, "Invalid dst index");
    }

    if (list_contains(g->adjlists[src], dst) == 0)
    {
        list_push(g->adjlists[src], dst);
    }

    if (g->directed == 0)
    {
        if (list_contains(g->adjlists[dst], src) == 0)
        {
            list_push(g->adjlists[dst], src);
        }
    }
}

void graph_remove_edge(struct graph *g, int src, int dst)
{
    if (src < 0 || src >= g->order)
    {
        err(EXIT_FAILURE, "Invalid src index");
    }

    if (dst < 0 || dst >= g->order)
    {
        err(EXIT_FAILURE, "Invalid dst index");
    }

    list_remove_val(g->adjlists[src], dst);

    if (g->directed == 0)
    {
        list_remove_val(g->adjlists[dst], src);
    }
}

struct graph *graph_add_vertex(struct graph *g)
{
    struct graph *tmp = (struct graph*)realloc(g, sizeof(struct graph) + sizeof(struct list*) * (g->order + 1));

    if (tmp == NULL)
    {
        err(EXIT_FAILURE, "Error while realloc");
    }
    g = tmp;
    g->order += 1;

    g->adjlists[g->order - 1] = (struct list*)malloc(sizeof(struct list));
    list_init(g->adjlists[g->order - 1]);

    return g;
}

void graph_print(struct graph *g)
{
    // Header
    printf(" == Print Graph ==\n");
    printf(" | Vertex: %5d |\n", g->order);
    if (g->directed == 1)
        printf(" | Directed: Yes |\n");
    else
        printf(" | Directed:  No |\n");
    printf(" =================\n");

    // Body
    for (int i = 0; i < g->order; i++)
    {
        printf(" V %2d: ", i);
        print_list(g->adjlists[i]);
    }
}

