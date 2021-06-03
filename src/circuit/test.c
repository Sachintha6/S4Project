#include <stdlib.h>
#include <stdio.h>
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"
#include "dijkstra.h"

int main()
{

    struct map* map = mgraph_load("../../files/data/paris.gra");
    
    mgraph_print(map->g);

    struct mgraph *r = shortest_ride(map->g, 26, 8);

    printf("\n\n-- RIDE GRAPH --\n");

    mgraph_print(r);

    printf("\n-- Pretty Print Ride --\n");

    int current_line = r->stations[0]->adjs->next->idline;
    int station_cpt = 0;
    printf("Prendre %s à %s\n", map->lines[r->stations[0]->adjs->next->idline]->name, r->stations[0]->name);

    for (int i = 0; i < r->order; i++)
    {
        if (i == r->order-1 || r->stations[i]->adjs->next->idline != current_line)
        {
            printf("Descendre à %s (%d stations)\n", r->stations[i]->name, station_cpt);
            
            if (i != r->order-1)
            {
                printf("Changement de ligne\n");
                printf("Prendre %s à %s\n", map->lines[r->stations[i]->adjs->next->idline]->name, r->stations[i]->name);
            }
            else
            {
                printf("Vous êtes arrivés !\n");
            }

            station_cpt = 0;
        }

        if (i != r->order - 1)
        {
            current_line = r->stations[i]->adjs->next->idline;
        }

        station_cpt++;
    }

    return 0;
}