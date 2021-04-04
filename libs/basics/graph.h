#ifndef _GRAPH_H_
#define _GRAPH_H_

struct graph
{
    int directed;
    int order;
    struct list *adjlists[1];
};

// Gen
struct graph *graph_init(int directed, int order);

// Add/rm elts
void graph_add_edge(struct graph *g, int src, int dst);
void graph_remove_edge(struct graph *g, int src, int dst);
struct graph *graph_add_vertex(struct graph *g);
//rm vertex

//Load/save
struct graph *graph_load(char *file);
void graph_save(char *file, struct graph *g);

//Display
void graph_print(struct graph *g);

#endif