#include <stdlib.h>

#include "default_matrix.h"
#include "constants.h"
#include "errors.h"

int input_matrix(FILE *f, int ***data, size_t *n, size_t *m)
{
    int **tmp;
    if (fscanf(f, "%zu %zu", n, m) != 2)
        return ERR_IO;

    if (*n > N || *m > M)
        return ERR_RANGE;

    tmp = allocate_matrix(*n, *m);
    if (tmp)
    {
        for (size_t i = 0; i < *n; ++i)
            for (size_t j = 0; j < *m; ++j)
                if (fscanf(f, "%d", &tmp[i][j]) != 1)
                {
                    free_matrix(tmp, *n);
                    return ERR_IO;
                }
    }
    else
        return ERR_MEM;

    *data = tmp;

    return ERR_OK;
}

int input_matrix_coord(FILE *f, int ***data, size_t *n, size_t *m)
{
    size_t col_non_null_el, row, column;
    int el;
    int **tmp;
    if (fscanf(f, "%zu %zu %zu", n, m, &col_non_null_el) != 3)
        return ERR_IO;

    if (*n > N || *m > M)
        return ERR_RANGE;

    tmp = allocate_matrix(*n, *m);
    if (tmp)
    {
        for (size_t i = 0; i < col_non_null_el; ++i)
        {
            if (fscanf(f, "%d %zu %zu", &el, &row, &column) != 3 || row > *n || column > *m || row == 0 || column == 0)
            {
                free_matrix(tmp, *n);
                return ERR_IO;
            }

            tmp[row - 1][column - 1] = el;
        }
    }
    else
        return ERR_MEM;

    *data = tmp;

    return ERR_OK;

}

void free_matrix(int **data, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(data[i]);

    free(data);
}

int** allocate_matrix(size_t n, size_t m)
{
    int **data;

    data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; ++i)
    {
        data[i] = calloc(m, sizeof(int));
        if (!data[i])
        {
            free_matrix(data, n);

            return NULL;
        }
    }

    return data;
}

int** sum_matrix(int **mat_a, int **mat_b, size_t n, size_t m)
{
    int **mat_sum = allocate_matrix(n, m);

    if (mat_sum)
    {
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                mat_sum[i][j] = mat_a[i][j] + mat_b[i][j];
    }

    return mat_sum;
}

void print_matrix(FILE *f, int **data, size_t n, size_t m)
{
    printf("\nMatrix is:\n");
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
            fprintf(f, "%d ", data[i][j]);

        fprintf(f, "\n");
    }
}

void print_matrix_coord(FILE *f, int **data, size_t n, size_t m)
{
    printf("\nMatrix is:\n");
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (data[i][j])
                fprintf(f, "%d %zu %zu\n", data[i][j], i + 1, j + 1);
}
