#ifndef VECTOR_H__
#define VECTOR_H__

#include <stdio.h>

typedef struct matrix_vec {
    size_t num_row;
    size_t num_col;
    size_t num_elems; 
    int *A;
    int *JA;
    int *IA;
} matrix_vec_t;

int input_vector(matrix_vec_t **mat_vec, int **data, size_t n, size_t m);

void free_vector(matrix_vec_t *mat_vec);

matrix_vec_t* sum_mat_vectors(matrix_vec_t *mat_a, matrix_vec_t *mat_b);

void output_vec(FILE *f, matrix_vec_t *mat_vec);

void output_vec_coord(FILE *f, matrix_vec_t *mat_vec);

#endif
