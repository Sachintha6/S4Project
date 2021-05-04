#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "mapGraph.h"
#include "list.h"

struct mgraph *mgraph_init(int directed, int order)
{
    struct mgraph *g = (struct mgraph*)malloc(
                            sizeof(struct mgraph) + 
                            sizeof(struct station*) * order);

    g->directed = directed;
    g->order = order;

    for (int i = 0; i < order; i++)
    {
        g->stations[i] = (struct station*)malloc(sizeof(struct station));
        g->stations[i]->name = "No Name";
        g->stations[i]->x = 0.0;
        g->stations[i]->y = 0.0;
        g->stations[i]->state = 1;

        g->stations[i]->adjs = (struct list*)malloc(sizeof(struct list)); 
        list_init(g->stations[i]->adjs);
    }

    return g;
}

void mgraph_add_edge(struct mgraph *g, int src, int dst, int idline)
{
    if (src < 0 || src >= g->order || g->stations[src]->state == 0)
        err(EXIT_FAILURE, "Invalid src index");

    if (dst < 0 || dst >= g->order || g->stations[dst]->state == 0)
        err(EXIT_FAILURE, "Invalid dst index");

    if (list_contains(g->stations[src]->adjs, dst) == 0)
    {
        list_push(g->stations[src]->adjs, dst, idline);
    }

    if (g->directed == 0)
    {
        if (list_contains(g->stations[dst]->adjs, src) == 0)
        {
            list_push(g->stations[dst]->adjs, src, idline);
        }
    }
}

void mgraph_remove_edge(struct mgraph *g, int src, int dst)
{
    if (src < 0 || src >= g->order || g->stations[src]->state == 0)
        err(EXIT_FAILURE, "Invalid src index");

    if (dst < 0 || dst >= g->order || g->stations[dst]->state == 0)
        err(EXIT_FAILURE, "Invalid dst index");

    list_remove_val(g->stations[src]->adjs, dst);

    if (g->directed == 0)
    {
        list_remove_val(g->stations[dst]->adjs, src);
    }
}

struct mgraph *mgraph_add_vertex(struct mgraph *g, char *name, double x, double y)
{
    //TODO: opti reuse removed vertex

    struct mgraph *tmp = (struct mgraph*)realloc(g, 
                                sizeof(struct mgraph) + 
                                sizeof(struct station*) * (g->order + 1));

    if (tmp == NULL)
        err(EXIT_FAILURE, "Error while realloc");
    
    g = tmp;
    g->order += 1;

    g->stations[g->order - 1] = (struct station*)malloc(sizeof(struct station));
    g->stations[g->order - 1]->name = name;
    g->stations[g->order - 1]->x = x;
    g->stations[g->order - 1]->y = y;
    g->stations[g->order - 1]->state = 1;
    g->stations[g->order - 1]->adjs = (struct list*)malloc(sizeof(struct list)); 
    list_init(g->stations[g->order - 1]->adjs);

    return g;
}

void mgraph_remove_vertex(struct mgraph *g, int id)
{
    g->stations[id]->name = "-rm";
    g->stations[id]->x = 0.0;
    g->stations[id]->y = 0.0;
    g->stations[id]->state = 0;
    g->stations[id]->adjs = NULL;

    for (int i = 0; i < g->order; i++)
    {
        if (g->stations[i]->state == 1)
        {
            list_remove_val(g->stations[i]->adjs, id);
        }
    }
}

int mgraph_get_station_by_position(struct mgraph *g, double x, double y, double range)
{
    for (int i = 0; i < g->order; i++)
    {
        if (g->stations[i]->x > x - range && g->stations[i]->x < x + range &&
            g->stations[i]->y > y - range && g->stations[i]->y < y + range &&
            g->stations[i]->state == 1)
        {
            return i;
        }
    }

    return -1;
}

struct mgraph *mgraph_load(char *file)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    char *stationsName;
    char *stationsPosX;
    char *stationsPosY;
    int order, directed = 0;

    // TODO: Verify file extension
    fp = fopen(file, "r");

    if (fp == NULL)
        err(EXIT_FAILURE, "Error while open file");

    if (getline(&line, &len, fp) == -1)
        err(EXIT_FAILURE, "Corrupted file");

    while (line[0] == '#')
    {
        char *ptr;
        char *rest;
        ptr = strtok(line, ":");
        rest = strtok(NULL, "");

        if (strcmp(ptr, "#stationsPosX") == 0)
        {
            stationsPosX = (char *)malloc(strlen(rest));
            strcpy(stationsPosX, rest);
        }
        else if (strcmp(ptr, "#stationsPosY") == 0)
        {
            stationsPosY = (char *)malloc(strlen(rest));
            strcpy(stationsPosY, rest);
        }
        else if (strcmp(ptr, "#stationsName") == 0)
        {
            stationsName = (char *)malloc(strlen(rest));
            strcpy(stationsName, rest);
        }

        if (getline(&line, &len, fp) == -1)
            err(EXIT_FAILURE, "Corrupted file");
    }
    
    directed = atoi(line);

    if (getline(&line, &len, fp) == -1)
        err(EXIT_FAILURE, "Corrupted file");
        
    order = atoi(line);

    struct mgraph *g = mgraph_init(directed, order);

    char *subp;
    char *subq;
    char *subd;

    for (int i = 0; i < order; i++)
    {
        subp = strtok_r(stationsPosX, " ", &stationsPosX);
        subq = strtok_r(stationsPosY, " ", &stationsPosY);
        subd = strtok_r(stationsName, ",", &stationsName);

        g->stations[i]->x = atof(subp);
        g->stations[i]->y = atof(subq);
        g->stations[i]->name = subd;
    }

    while (getline(&line, &len, fp) != -1)
    {
        char *ptr;

        //TODO: Catch error
        ptr = strtok(line, " ");
        int src = atoi(ptr);
        ptr = strtok(NULL, " ");
        int dst = atoi(ptr);
        ptr = strtok(NULL, " ");
        int idline = atoi(ptr);

        //ignore rest of line
        mgraph_add_edge(g, src, dst, idline);
    }

    fclose(fp);
    if (line)
        free(line);

    return g;
}

void mgraph_save(char *file, struct mgraph *g, struct line *lines[])
{
    FILE *fp;

    // TODO: Verify file extension
    fp = fopen(file, "w");

    if (fp == NULL)
        err(EXIT_FAILURE, "Error while open file");

    //Headers

    fprintf(fp, "#linesName:");
    for (int i = 0; i < 15; i++)
        fprintf(fp, "%s,", lines[i]->name);
    fprintf(fp, "\n");

    fprintf(fp, "#linesColor:");
    for (int i = 0; i < 15; i++)
        fprintf(fp, "%s,", lines[i]->color);
    fprintf(fp, "\n");

    fprintf(fp, "#stationsName:");
    for (int i = 0; i < g->order; i++)
        fprintf(fp, "%s,", g->stations[i]->name);
    fprintf(fp, "\n");

    fprintf(fp, "#stationsPosX:");
    for (int i = 0; i < g->order; i++)
        fprintf(fp, "%f ", g->stations[i]->x);
    fprintf(fp, "\n");

    fprintf(fp, "#stationsPosY:");
    for (int i = 0; i < g->order; i++)
        fprintf(fp, "%f ", g->stations[i]->y);
    fprintf(fp, "\n");

    //Body

    fprintf(fp, "%d\n", g->directed);
    fprintf(fp, "%d\n", g->order);

    //TODO: opti: only one edge when for no directed graph
    for (int i = 0; i < g->order; i++)
    {
        struct list *list = g->stations[i]->adjs;
        while (list->next != NULL)
        {
            list = list->next;
            fprintf(fp, "%d %d %d\n", i, list->data, list->idline);
        }
    }

    fclose(fp);
    //return error/success value ?
}

void mgraph_print(struct mgraph *g)
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
        if (g->stations[i]->state == 1)
        {
            printf("%2d - %s (%4.0f|%4.0f): ", i, g->stations[i]->name, g->stations[i]->x, g->stations[i]->y);
            print_list(g->stations[i]->adjs);
        }
        else
        {
            printf("%2d - Removed\n", i);
        }
    }
}

