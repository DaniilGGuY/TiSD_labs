#include <stdlib.h>

#include "vector.h"
#include "errors.h"

int input_vector(matrix_vec_t **mat_vec, int **data, size_t n, size_t m)
{
    matrix_vec_t *tmp = malloc(sizeof(matrix_vec_t));
    if (tmp)
    {
        size_t col = 0, ind_pointer = 0, ind_elem = 0;
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                if (data[i][j])
                    ++col;

        tmp->num_row = n;
        tmp->num_col = m;
        tmp->num_elems = col;
        tmp->A = malloc(col * sizeof(int));
        tmp->JA = malloc(col * sizeof(int));
        tmp->IA = malloc((n + 1) * sizeof(int));

        if (tmp->A && tmp->JA && tmp->IA)
        {
            for (size_t i = 0; i < n; ++i)
            {
                tmp->IA[ind_pointer] = ind_elem;
                ++ind_pointer;
                for (size_t j = 0; j < m; ++j)
                {
                    if (data[i][j])
                    {
                        tmp->A[ind_elem] = data[i][j];
                        tmp->JA[ind_elem] = j;
                        ++ind_elem;
                    }
                }
            }
        }
        else
        {
            free_vector(tmp);
            return ERR_MEM;
        }

        tmp->IA[n] = tmp->num_elems;
        *mat_vec = tmp;
    }
    else
        return ERR_MEM;

    return ERR_OK;
}

void free_vector(matrix_vec_t *mat_vec)
{
    free(mat_vec->A);
    free(mat_vec->JA);
    free(mat_vec->IA);
    free(mat_vec);
}

matrix_vec_t* sum_mat_vectors(matrix_vec_t *mat_a, matrix_vec_t *mat_b)
{
    matrix_vec_t *mat_c = malloc(sizeof(matrix_vec_t));
    if (!mat_c)
        return NULL;
    int ind_a, ind_b, ind_c_elem = 0, ind_c_pointer = 0;
    mat_c->num_col = mat_a->num_col;
    mat_c->num_row = mat_a->num_row;
    mat_c->num_elems = mat_a->num_elems + mat_b->num_elems;

    for (size_t i = 0; i < mat_a->num_row; ++i)
    {
        ind_a = 0, ind_b = 0;
        while (ind_a < mat_a->IA[i + 1] - mat_a->IA[i] && ind_b < mat_b->IA[i + 1] - mat_b->IA[i])
        {
            if (mat_a->JA[mat_a->IA[i] + ind_a] == mat_b->JA[mat_b->IA[i] + ind_b])
            {
                --mat_c->num_elems;
                ++ind_a;
                ++ind_b;
            }
            else if (mat_a->JA[mat_a->IA[i] + ind_a] > mat_b->JA[mat_b->IA[i] + ind_b])
                ++ind_b;
            else
                ++ind_a;
        }
    }

    mat_c->A = malloc(mat_c->num_elems * sizeof(int));
    mat_c->JA = malloc(mat_c->num_elems * sizeof(int));
    mat_c->IA = malloc((mat_c->num_row + 1) * sizeof(int));
    mat_c->IA[mat_c->num_row] = mat_c->num_elems;
    if (mat_c->A && mat_c->JA && mat_c->IA)
    {
        for (size_t i = 0; i < mat_c->num_row; ++i)
        {
            mat_c->IA[ind_c_pointer] = ind_c_elem;
            ++ind_c_pointer;
            ind_a = 0, ind_b = 0;
            while (ind_a < mat_a->IA[i + 1] - mat_a->IA[i] && ind_b < mat_b->IA[i + 1] - mat_b->IA[i])
            {
                if (mat_a->JA[mat_a->IA[i] + ind_a] == mat_b->JA[mat_b->IA[i] + ind_b])
                {
                    mat_c->A[ind_c_elem] = mat_a->A[mat_a->IA[i] + ind_a] + mat_b->A[mat_b->IA[i] + ind_b];
                    mat_c->JA[ind_c_elem] = mat_a->JA[mat_a->IA[i] + ind_a];
                    ++ind_b;
                    ++ind_a;
                }
                else if (mat_a->JA[mat_a->IA[i] + ind_a] > mat_b->JA[mat_b->IA[i] + ind_b])
                {
                    mat_c->A[ind_c_elem] = mat_b->A[mat_b->IA[i] + ind_b];
                    mat_c->JA[ind_c_elem] = mat_b->JA[mat_b->IA[i] + ind_b];
                    ++ind_b;
                }
                else
                {
                    mat_c->A[ind_c_elem] = mat_a->A[mat_a->IA[i] + ind_a];
                    mat_c->JA[ind_c_elem] = mat_a->JA[mat_a->IA[i] + ind_a];
                    ++ind_a;
                }

                ++ind_c_elem;
            }
            while (ind_b < mat_b->IA[i + 1] - mat_b->IA[i])
            {
                mat_c->A[ind_c_elem] = mat_b->A[mat_b->IA[i] + ind_b];
                mat_c->JA[ind_c_elem] = mat_b->JA[mat_b->IA[i] + ind_b];
                ++ind_b;
                ++ind_c_elem;
            }
            while (ind_a < mat_a->IA[i + 1] - mat_a->IA[i])
            {
                mat_c->A[ind_c_elem] = mat_a->A[mat_a->IA[i] + ind_a];
                mat_c->JA[ind_c_elem] = mat_a->JA[mat_a->IA[i] + ind_a];
                ++ind_a;
                ++ind_c_elem;
            }
        } 
    }
    else
        free_vector(mat_c);

    return mat_c;
}

void output_vec(FILE *f, matrix_vec_t *mat_vec)
{
    fprintf(f, "\nVector is:\n");
    if (mat_vec)
    {
        int ind_el;
        for (size_t i = 0; i < mat_vec->num_row; ++i)
        {
            ind_el = 0;
            for (size_t j = 0; j < mat_vec->num_col; ++j)
            {
                if (ind_el < mat_vec->IA[i + 1] - mat_vec->IA[i] && mat_vec->JA[mat_vec->IA[i] + ind_el] == (int)j)
                {
                    fprintf(f, "%d ", mat_vec->A[mat_vec->IA[i] + ind_el]);
                    ++ind_el;
                }
                else
                    fprintf(f, "0 ");
            }
            fprintf(f, "\n");
        }
    }
    else
        fprintf(f, "Nothing in res!\n");
}

void output_vec_coord(FILE *f, matrix_vec_t *mat_vec)
{
    fprintf(f, "\nVector is:\n");
    if (mat_vec)
        for (size_t i = 0; i < mat_vec->num_row; ++i)
            for (int ind = 0; ind < mat_vec->IA[i + 1] - mat_vec->IA[i]; ++ind)
                fprintf(f, "%d %zu %d", mat_vec->A[mat_vec->IA[i] + ind], i + 1, mat_vec->JA[mat_vec->IA[i] + ind] + 1);
    else
        fprintf(f, "Nothing in res!\n");
}
