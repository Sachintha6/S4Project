#ifndef _MAP_GRAPH_H_
#define _MAP_GRAPH_H_

struct map
{
    int nblines;
    int save_state;
    const char *filename;
    const char *name;
    const char *backgroundImg;
    struct mgraph *g;
    struct line *current_line;
    struct line *lines[];
};

struct mgraph
{
    int directed;
    int order;
    struct station *stations[];
};

struct station
{
    char *name;
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
struct map *mgraph_load(char *file);
int mgraph_save(const char *file, struct map *map);

//Display
void mgraph_print(struct mgraph *g);

#endif