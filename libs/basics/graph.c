#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
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
        err(EXIT_FAILURE, "Invalid src index");

    if (dst < 0 || dst >= g->order)
        err(EXIT_FAILURE, "Invalid dst index");

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
        err(EXIT_FAILURE, "Invalid src index");

    if (dst < 0 || dst >= g->order)
        err(EXIT_FAILURE, "Invalid dst index");

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
        err(EXIT_FAILURE, "Error while realloc");
    
    g = tmp;
    g->order += 1;

    g->adjlists[g->order - 1] = (struct list*)malloc(sizeof(struct list));
    list_init(g->adjlists[g->order - 1]);

    return g;
}

struct graph *graph_load(char *file)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int order, directed = 0;

    // TODO: Verify file extension
    fp = fopen(file, "r");

    if (fp == NULL)
        err(EXIT_FAILURE, "Error while open file");

    // comments
    if (getline(&line, &len, fp) == -1)
        err(EXIT_FAILURE, "Corrupted file");

    while (line[0] == '#')
    {
        if (getline(&line, &len, fp) == -1)
            err(EXIT_FAILURE, "Corrupted file");
    }
    
    directed = atoi(line);

    if (getline(&line, &len, fp) == -1)
        err(EXIT_FAILURE, "Corrupted file");
        
    order = atoi(line);

    struct graph *g = graph_init(directed, order);

    while (getline(&line, &len, fp) != -1)
    {
        char *ptr;

        //TODO: Catch error
        ptr = strtok(line, " ");
        int src = atoi(ptr);

        ptr = strtok(NULL, " ");
        int dst = atoi(ptr);

        //ignore rest of line
        graph_add_edge(g, src, dst);
    }

    fclose(fp);
    if (line)
        free(line);

    return g;
}

void graph_save(char *file, struct graph *g)
{
    FILE *fp;

    // TODO: Verify file extension
    fp = fopen(file, "w");

    if (fp == NULL)
        err(EXIT_FAILURE, "Error while open file");

    fprintf(fp, "%d\n", g->directed);
    fprintf(fp, "%d\n", g->order);

    //TODO: opti: only one edge when for no directed graph
    for (int i = 0; i < g->order; i++)
    {
        struct list *list = g->adjlists[i];
        while (list->next != NULL)
        {
            fprintf(fp, "%d %d\n", i, list->data);
            list = list->next;            
        }
    }

    fclose(fp);
    //return error/success value ?
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

