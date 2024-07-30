#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "algos.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "err_codes.h"

void description()
{
    printf("This program imitate work with graph\n\n");
}

void menu()
{
    printf("Input action:\n");
    printf("1 - if you want to input graph from file\n");
    printf("2 - if you want to input graph by yourself\n");
    printf("3 - find longest simple path in graph\n");
    printf("4 - export dot\n");
    printf("0 - if you want to leave from program\n");
}

int read_str(char **buf)
{
    ssize_t read; 
    size_t len = 0;
    int rc = OK;
    char *tmp = NULL;

    if ((read = getline(&tmp, &len, stdin)) == -1)
        rc = ERR_MEM;
    if (read <= 1 && !rc)
        rc = ERR_IO;
    if (!rc && tmp[read - 1] == '\n')
        tmp[read - 1] = '\0';

    *buf = tmp;

    return rc;
}

int main()
{
    FILE *f;
    graph_t *graph = NULL;
    char *name = NULL;
    int action, rc = OK;
    bool is_end = false;
    //clock_t beg, end;

    description();
    while (!rc && !is_end)
    {
        menu();
        if (scanf("%d", &action) != 1)
            rc = ERR_IO;
        else
            (void)getc(stdin);

        switch(action)
        {
            case 1:
                if (graph)
                    graph_destroy(graph);

                printf("Input filename:\n");
                rc = read_str(&name);
                if (!rc)
                {
                    f = fopen(name, "r");
                    if (f)
                    {
                        rc = graph_read(f, &graph);
                        if (!rc)
                            printf("Successfully read from file!\n");
                        else 
                            printf("Errors with reading from file\n");

                        fclose(f);
                    }
                    else
                        rc = ERR_FILE;

                    free(name);
                }
                else
                    rc = ERR_FILE;

                break;
            case 2:
                if (graph)
                    graph_destroy(graph);

                rc = graph_read(stdin, &graph);
                if (!rc)
                    printf("Successfully read!\n");
                else 
                    printf("Errors with reading\n");

                break;
            case 3:
                if (!graph)
                {
                    printf("Graph is empty\n");
                    rc = ERR_IO;
                }

                printf("Input filename when you want to output path:\n");
                rc = read_str(&name);
                if (!rc)
                {
                    f = fopen(name, "w");
                    if (f)
                    {
                        //beg = clock();
                        //for (size_t i = 0; i < 1000; ++i)
                        rc = find_longest_simple_path(f, graph);
                        //end = clock();
                        //printf("Printed in %lf seconds!\n", (double)(end - beg) / CLOCKS_PER_SEC * 1000);
                        printf("Successfully printed in file!\n");
                        fclose(f);
                    }
                    else
                        rc = ERR_FILE;

                    free(name);
                }
                else
                    rc = ERR_FILE;

                break;
            case 4:
                printf("Input output file name:\n");
                rc = read_str(&name);
                if (!rc)
                {
                    f = fopen(name, "w");
                    if (f)
                    {
                        graph_print_dot(f, graph);
                        printf("Successfully printed in file!\n");
                        fclose(f);
                    }
                    else
                        rc = ERR_FILE;

                    free(name);
                }
                else
                    rc = ERR_FILE;

                break;
            case 0:
                is_end = true;

                break;
            default:
                rc = ERR_IO;

                break;
        }
    }

    if (graph)
        graph_destroy(graph);
    
    return rc;
}