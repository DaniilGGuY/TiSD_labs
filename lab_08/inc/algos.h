#ifndef ALGOS_H__
#define ALGOS_H__

#include <stdio.h>

#include "graph.h"

void dfs(int vert, graph_t *graph, int paint[], int path[], int cur_len,  int max_path[], int *max_len);

int find_longest_simple_path(FILE *f, graph_t *graph);

#endif