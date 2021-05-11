#include <stdlib.h>
#include <stdio.h>
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"

int choose_min(int *dist, int *m, int len)
{
    int x = -1;
    int mini = -1;

    for (int i = 0; i < len;i++)
    {
        if (mini == -1 || (m[i] && dist[i] < mini ))
        {
            x = i;
            mini = dist[i];
        }
    }

    return x;
}

void dijkstra(struct mgraph *g, int src)
{
    // Init
    int dist[g->order];
    dist[src] = 0;
    int p[g->order];
    p[src] = -1;
    int m[g->order];
    struct list *visited = (struct list*)malloc(sizeof(struct list));
    int n =1;
    int x = src;

    while (x != -1 && n < g->order)
    {
        
        list_push(visited, x, -1);
        m[x] = 0;
        struct list *l = g->stations[x]->adjs;

        while (l->next != NULL)
        {
            int y = l->data;
            //printf("== %d\n", y);

            if (dist[x] + 1 < dist[y])
            {
                dist[y] = dist[x] + 1;
                p[y] = x;
            }

            l = l->next;
        }

        x = choose_min(dist, m, g->order);
        printf("choose min: %d\n", x);
        n += 1;

    }

    print_list(visited);
    printf("=== Dist === \n");

    for (int i = 0; i < g->order; i++)
    {
        printf("%d|", dist[i]);
    }

    printf("\n");

}