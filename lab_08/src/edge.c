#include <stdlib.h>

#include "edge.h"

edge_t *edge_create(int start, int finish, int cost)
{
    edge_t *edge = malloc(sizeof(edge_t));
    if (edge)
    {
        edge->start = start;
        edge->finish = finish;
        edge->cost = cost;
        edge->next = NULL;
    }

    return edge;
}

void edge_clear(edge_t *edge)
{
    free(edge);
}

void edge_print(edge_t *edge)
{
    printf("From %d to %d cost %d\n", edge->start + 1, edge->finish + 1, edge->cost);
}

void edge_print_dot(FILE *f, edge_t *edge)
{
    fprintf(f, "%d -> %d [label=\"%d\"];\n", edge->start + 1, edge->finish + 1, edge->cost);
}