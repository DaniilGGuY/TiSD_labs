#include <stdlib.h>

#include "node.h"

node_t *node_create(int start)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->start = start;
        node->connected = NULL;
    }

    return node;
}

void node_insert(node_t *node, edge_t *edge)
{
    edge_t *cur = node->connected;
    if (!cur)
        node->connected = edge;
    else
    {
        while (cur->next)
            cur = cur->next;

        cur->next = edge;
    }
}

void node_destroy(node_t *node)
{
    node_make_empty(node);
    free(node);
}

void node_make_empty(node_t *node)
{
    edge_t *cur = node->connected, *next;
    while (cur)
    {
        next = cur->next;
        edge_clear(cur);
        cur = next;
    }
}

void node_print(node_t *node)
{
    edge_t *cur = node->connected;
    while (cur)
    {
        edge_print(cur);
        cur = cur->next;
    }
}

void node_print_dot(FILE *f, node_t *node)
{
    edge_t *cur = node->connected;
    while (cur)
    {
        edge_print_dot(f, cur);
        cur = cur->next;
    }
}
