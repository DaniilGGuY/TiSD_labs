#ifndef EDGE_H__
#define EDGE_H__

#include <stdio.h>

typedef struct edge_type
{
    int start;
    int finish;
    int cost;
    struct edge_type *next;
} edge_t;

edge_t *edge_create(int start, int finish, int cost);

void edge_clear(edge_t *edge);

void edge_print(edge_t *edge);

void edge_print_dot(FILE *f, edge_t *edge);

#endif