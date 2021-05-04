#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

int choose_min(int *dist, int *m, int len);
void dijkstra(struct mgraph *g, int src);

#endif