#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "algos.h"
#include "err_codes.h"

void dfs(int vert, graph_t *graph, int paint[], int path[], int cur_len,  int max_path[], int *max_len) 
{
    paint[vert] = 1;
    path[cur_len++] = vert;

    if (cur_len > *max_len)
    {
        *max_len = cur_len;
        for (int i = 0; i < cur_len; i++)
            max_path[i] = path[i];
    }

    edge_t *cur = graph->array[vert]->connected;
    while (cur)
    {
        if (!paint[cur->finish] && cur)
            dfs(cur->finish, graph, paint, path, cur_len, max_path, max_len);

        cur = cur->next;
    }

    paint[vert] = false;
    --cur_len;
}

int find_longest_simple_path(FILE *f, graph_t *graph)
{

    int max_path_len = 0;

    int *path = malloc(graph->size * sizeof(int));
    if (!path)
    {
        printf("Error mem\n");
        return ERR_MEM;
    }

    int *paint = calloc(graph->size, sizeof(int));
    if (!paint)
    {
        free(path);
        printf("Error mem\n");
        return ERR_MEM;
    }

    int *max_path = malloc(graph->size * sizeof(int));
    if (!max_path)
    {
        free(path);
        free(paint);
        printf("Error mem\n");
        return ERR_MEM;
    }

    for (size_t i = 0; i < graph->size; i++)
        dfs(i, graph, paint, path, 0, max_path, &max_path_len);

    fprintf(f, "digraph outgraph {\n");
    for (int i = 0; i < max_path_len; ++i)
    {
        fprintf(f, "%d;\n", max_path[i] + 1);
        if (i >= 1)
            fprintf(f, "%d -> %d [label=\"1\"];\n", max_path[i - 1] + 1, max_path[i] + 1);
    }
    fprintf(f, "}\n");

    free(path);
    free(max_path);
    free(paint);

    return OK;
}

