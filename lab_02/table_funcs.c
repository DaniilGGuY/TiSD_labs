#include "table_funcs.h"
#include "stud_funcs.h"
#include "error.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int upload_table(FILE *f, student_t *table, size_t *n)
{
    int rc = ERR_OK;
    *n = 0;
    while (!feof(f) && !rc)
    {
        rc = stud_read(f, table + *n);
        ++(*n);
    }

    --(*n);
    return ERR_OK;  
}

void print_table(FILE *f, student_t *table, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        stud_print(f, table + i);
}

void print_table_by_keys(FILE *f, student_t *table, key_field_t *key, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        stud_print(f, table + key[i].index);
}

int add_row(student_t *table, size_t *n)
{
    int rc = ERR_OK;
    if (*n == N)
        rc = ERR_OVERFLOW;

    if (!rc)
    {
        rc = stud_read_from_terminal(table + *n);
        ++(*n);
    }

    return rc;
}

int delete_row(student_t *table, size_t *n, size_t num_str)
{
    int rc = ERR_OK;
    if (num_str > *n)
        rc = ERR_OVERFLOW;
    else
    {
        for (size_t i = num_str; i < *n; ++i)
            memcpy(table + i - 1, table + i, sizeof(student_t));

        --(*n);
    }

    return rc;
}

void create_table_keys(student_t *table, key_field_t *keys, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        keys[i].index = i;
        strcpy(keys[i].surname, table[i].surname); 
    }
}

void print_table_keys(key_field_t *keys, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%zu %s\n", keys[i].index, keys[i].surname);
}

void bubble_sort_table(student_t *table, size_t n)
{
    clock_t beg, end;
    beg = clock();
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n - i - 1; ++j)
        {
            if (strcmp(table[j].surname, table[j + 1].surname) > 0)
            {
                student_t tmp;
                memcpy(&tmp, &table[j], sizeof(student_t));
                memcpy(&table[j], &table[j + 1], sizeof(student_t));
                memcpy(&table[j + 1], &tmp, sizeof(student_t));
            }
        }
    }
    end = clock();
    double res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0;
    printf("Table sorted in %lf milliseconds\n", res);
}

void bubble_sort_table_keys(key_field_t *keys, size_t n)
{
    clock_t beg, end;
    beg = clock();
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n - i - 1; ++j)
        {
            if (strcmp(keys[j].surname, keys[j + 1].surname) > 0)
            {
                student_t tmp;
                memcpy(&tmp, &keys[j], sizeof(key_field_t));
                memcpy(&keys[j], &keys[j + 1], sizeof(key_field_t));
                memcpy(&keys[j + 1], &tmp, sizeof(key_field_t));
            }
        }
    }
    end = clock();
    double res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0;
    printf("Table sorted in %lf milliseconds\n", res);
}

int comp_studs(const void *a, const void *b)
{
    student_t *pl = (student_t *)a;
    student_t *pr = (student_t *)b;

    char *surname_l = pl->surname;
    char *surname_r = pr->surname;

    return strcmp(surname_l, surname_r);
}

void qsort_table(student_t *table, size_t n)
{
    clock_t beg, end;
    beg = clock();
    qsort(table, n, sizeof(student_t), comp_studs);
    end = clock();
    double res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0;
    printf("Table sorted in %lf milliseconds\n", res);
}

int comp_studs_by_keys(const void *a, const void *b)
{
    key_field_t *pl = (key_field_t *)a;
    key_field_t *pr = (key_field_t *)b;

    char *surname_l = pl->surname;
    char *surname_r = pr->surname;

    return strcmp(surname_l, surname_r);
}

void qsort_table_keys(key_field_t *keys, size_t n)
{
    clock_t beg, end;
    beg = clock();
    qsort(keys, n, sizeof(key_field_t), comp_studs_by_keys);
    end = clock();
    double res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0;
    printf("Table sorted in %lf milliseconds\n", res);
}

void filter_output(student_t *table, size_t n, size_t year)
{
    size_t count = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (table[i].date.year == year)
        {
            ++count;
            stud_print(stdout, table + i);
        }
    }

    if (count == 0)
        printf("No one correct field!\n");
}