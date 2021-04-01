#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "list.h"

int main()
{
    struct graph *g = graph_init(1, 6);
    
    graph_print(g);

    return 0;
}