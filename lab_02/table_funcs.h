#ifndef TABLE_FUNCS_H__
#define TABLE_FUNCS_H__

#include <stdio.h>
#include "table.h"

int upload_table(FILE *f, student_t *table, size_t *n);

void print_table(FILE *f, student_t *table, size_t n);

void print_table_by_keys(FILE *f, student_t *table, key_field_t *key, size_t n);

int add_row(student_t *table, size_t *n);

int delete_row(student_t *table, size_t *n, size_t num_str);

void create_table_keys(student_t *table, key_field_t *keys, size_t n);

void print_table_keys(key_field_t *keys, size_t n);

void bubble_sort_table(student_t *table, size_t n);

void bubble_sort_table_keys(key_field_t *keys, size_t n);

int comp_studs(const void *a, const void *b);

void qsort_table(student_t *table, size_t n);

int comp_studs_by_keys(const void *a, const void *b);

void qsort_table_keys(key_field_t *keys, size_t n);

void filter_output(student_t *table, size_t n, size_t year);

#endif