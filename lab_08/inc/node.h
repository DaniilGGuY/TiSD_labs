#ifndef NODE_H__
#define NODE_H__

#include <stdio.h>

#include "edge.h"

typedef struct node_type
{
    int start;
    edge_t *connected;
} node_t;

node_t *node_create(int start);

void node_insert(node_t *node, edge_t *edge);

void node_destroy(node_t *node);

void node_make_empty(node_t *node);

void node_print(node_t *node);

void node_print_dot(FILE *f, node_t *node);

#endif