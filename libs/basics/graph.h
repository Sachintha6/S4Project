#ifndef _GRAPH_H_
#define _GRAPH_H_

struct graph
{
    int directed;
    int order;
    struct list *adjlists[1];
};

struct graph* graph_init( int directed, int order);
void graph_print(struct graph *g);

#endif