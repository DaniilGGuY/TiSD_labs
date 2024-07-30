#ifndef GRAPH_H__
#define GRAPH_H__

#include <stdio.h>

#include "node.h"
#include "edge.h"

typedef struct graph_type
{
    size_t size;
    node_t **array;
} graph_t;

graph_t *graph_create(size_t size);

void graph_destroy(graph_t *graph);

void graph_print(graph_t *graph);

void graph_print_dot(FILE *f, graph_t *graph);

int graph_read(FILE *f, graph_t **graph);

#endif