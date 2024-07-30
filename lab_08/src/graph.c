#include <stdlib.h>

#include "graph.h"
#include "err_codes.h"

graph_t *graph_create(size_t size)
{
    graph_t *graph = malloc(sizeof(graph_t));
    if (graph)
    {
        graph->size = size;
        graph->array = malloc(size * sizeof(node_t *));
        if (!graph->array)
            free(graph);
        else
        {
            for (size_t i = 0; i < size; ++i)
                graph->array[i] = node_create(i);
        }
    }

    return graph;
}

void graph_destroy(graph_t *graph)
{
    for (size_t i = 0; i < graph->size; ++i)
        node_destroy(graph->array[i]);

    free(graph->array);
    free(graph);
}

void graph_print(graph_t *graph)
{
    for (size_t i = 0; i < graph->size; ++i)
        node_print(graph->array[i]);
}

void graph_print_dot(FILE *f, graph_t *graph)
{
    fprintf(f, "digraph outgraph {\n");

    for (size_t i = 0; i < graph->size; ++i)
        fprintf(f, "%d;\n", graph->array[i]->start + 1);

    for (size_t i = 0; i < graph->size; ++i)
        node_print_dot(f, graph->array[i]);

    fprintf(f, "}\n");
}

int graph_read(FILE *f, graph_t **graph)
{
    size_t vertexes_col, edges_col;
    if (f == stdin)
        printf("Input num of vertexes and num of edges in graph:\n");

    if (fscanf(f, "%zu %zu", &vertexes_col, &edges_col) != 2 || vertexes_col == 0)
        return ERR_IO;

    graph_t *tmp = graph_create(vertexes_col);

    if (!tmp)
        return ERR_MEM;

    int rc = OK, start, finish, cost = 1;
    if (f == stdin)
        printf("Input edges in format (index form 0): START (< %zu) FINISH (< %zu) COST\n", edges_col, edges_col);
    
    for (size_t i = 0; i < edges_col && !rc; ++i)
    {   
        if (fscanf(f, "%d %d", &start, &finish) != 2 || (size_t)start > vertexes_col || start == 0 || (size_t)finish > vertexes_col || finish == 0)
            rc = ERR_IO;

        if (!rc)
        {
            edge_t *edge = edge_create(start - 1, finish - 1, cost);
            if (edge)
                node_insert(tmp->array[start - 1], edge);
            else
                rc = ERR_MEM;
        }
    }

    if (!rc)
        *graph = tmp;
    else
        graph_destroy(tmp);

    return rc;
}