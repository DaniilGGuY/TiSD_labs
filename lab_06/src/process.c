#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "process.h"
#include "err_codes.h"

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

int read_int(int *val)
{
    if (scanf("%d", val) != 1 || *val < 0)
        return ERR_IO;
    
    return OK;
}

int read_node(tree_t **pt)
{
    tree_t *tmp = *pt;
    char *filename = NULL, *access = NULL, *size = NULL, *owner = NULL;
    int year, month, day, hour, minutes, rc = OK;
    *pt = NULL;
    if (!rc)
    {
        printf("Input a filename:\n");
        rc = read_str(&filename);
    }

    if (!rc)
    {
        printf("Input an access of file:\n");
        rc = read_str(&access);
    }

    if (!rc)
    {
        printf("Input an owner of file:\n");
        rc = read_str(&owner);
    }

    if (!rc)
    {
        printf("Input a size of file:\n");
        rc = read_str(&size);
    }
    
    if (!rc)
    {
        printf("Input a year of last touch:\n");
        rc = read_int(&year);
    }
    
    if (!rc)
    {
        printf("Input a month of last touch:\n");
        rc = read_int(&month);    
    }

    if (!rc)
    {
        printf("Input a day of last touch:\n");
        rc = read_int(&day);    
    }

    if (!rc)
    {
        printf("Input a hour of last touch:\n");
        rc = read_int(&hour);    
    }
    
    if (!rc)
    {
        printf("Input a minute of last touch:\n");
        rc = read_int(&minutes);
    }

    if (!rc)
    {
        tmp = tree_create(filename, access, owner, size, year, month, day, hour, minutes);
        printf("%s %s %s %s %d %d %d %d %d\n", tmp->filename, tmp->access, tmp->owner, tmp->size, tmp->year, tmp->month, tmp->day, tmp->hour, tmp->minutes);
        if (!tmp)
            rc = ERR_MEM;
        else
            *pt = tmp;
    }

    if (rc)
    {
        if (filename)
            free(filename);
        if (access)
            free(access);
        if (owner)
            free(owner);
        if (size)
            free(size);
    }
        
    return rc;
}