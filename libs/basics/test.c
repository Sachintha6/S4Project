#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "list.h"

int main()
{
    struct graph *g;

    printf("=== Start init ===\n");

    g = graph_init(1, 13);
    
    printf("=== Start debugging ===\n");

    graph_print(g);

    return 0;
}