#ifndef DEFAULT_MATRIX_H__
#define DEFAULT_MATRIX_H__

#include <stdio.h>

int input_matrix(FILE *f, int ***data, size_t *n, size_t *m);

int input_matrix_coord(FILE *f, int ***data, size_t *n, size_t *m);

void free_matrix(int **data, size_t n);

int** allocate_matrix(size_t n, size_t m);

int** sum_matrix(int **mat_a, int **mat_b, size_t n, size_t m);
    
void print_matrix(FILE *f, int **data, size_t n, size_t m);

void print_matrix_coord(FILE *f, int **data, size_t n, size_t m);

#endif
