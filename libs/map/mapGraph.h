#ifndef _MAP_GRAPH_H_
#define _MAP_GRAPH_H_

struct mgraph
{
    int directed;
    int order;
    struct station *stations[];
};

struct station
{
    const char *name;
    double x;
    double y;
    int state;
    struct list *adjs;
};

struct line
{
    int idline;
    const char *name;
    const char *color;
};

// Gen
struct mgraph *mgraph_init(int directed, int order);

// Add/rm elts
void mgraph_add_edge(struct mgraph *g, int src, int dst, int idline);
void mgraph_remove_edge(struct mgraph *g, int src, int dst);
struct mgraph *mgraph_add_vertex(struct mgraph *g, char *name, double x, double y);
void mgraph_remove_vertex(struct mgraph *g, int id);
//rm vertex

// Interaction w/ GUI
int mgraph_get_station_by_position(struct mgraph *g, double x, double y, double range);

//Load/save
struct mgraph *mgraph_load(char *file);
void mgraph_save(char *file, struct mgraph *g, struct line *lines[]);

//Display
void mgraph_print(struct mgraph *g);

#endif