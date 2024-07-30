#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "default_matrix.h"
#include "errors.h"
#include "vector.h"

typedef int (*reader_t)(FILE *f, int ***data, size_t *n, size_t *m);

int check_file(FILE **f, char *mods)
{
    char str[FILE_NAME + 1];
    int rc = ERR_OK;
    if (scanf("%s", str) != 1)
        rc = ERR_IO;
    else
    {
        if (strncmp("stdin", str, strlen("stdin")) == 0)
            *f = stdin;
        else
        {
            *f = fopen(str, mods);
            if (!(*f))
                rc = ERR_FILE;
        }
    }
    
    return rc;
}

void description()
{
    printf("This program sum matrix A with matrix B in matrix C by 2 methods\n");
    printf("You can choose, how to input/output matrix\n\n");
    printf("To input matrix coordinatly you need to input sizes of matrix and col non null elements\n");
    printf("Then you can input non null elements in format: element row column\n\n");
    printf("To input matrix you need to input sizes before and then input elements\n\n");
}

int read_matrix(FILE **f, reader_t reader, int ***mat, size_t *n, size_t *m, matrix_vec_t **vec)
{
    int rc = check_file(f, "r");
    printf("Input matrix\n");
    if (!rc)
    {
        rc = reader(*f, mat, n, m);
        if (!rc)
        {
            rc = input_vector(vec, *mat, *n, *m);
            if (rc)
                printf("Errors with create vector\n");
        }
        else
            printf("Incorrect input of matrix\n");
    }
    else
        printf("Errors with open file\n");

    return rc;
}

int main(void)
{
    FILE *f;
    int **mat_a, **mat_b, **mat_c;
    size_t na, ma, nb, mb;
    int rc = ERR_OK, way_inout;
    matrix_vec_t *vec_a = NULL, *vec_b = NULL, *vec_c = NULL;
    //clock_t beg, end;
    //double res;

    description();
    printf("Choose format to input matrix\n");
    printf("Type 1 to input full matrix\n");
    printf("Type 2 to input coordinatly\n");
    if (scanf("%d", &way_inout) != 1 || way_inout > 2 || way_inout < 1)
    {
        printf("Incorrect format of matrix-input method\n");
        rc = ERR_IO;
    }

    if (!rc)
    {
        printf("Input file name for matrix A. Input stdin if you want to input matrix yourself: ");
        rc = read_matrix(&f, (way_inout == 1) ? input_matrix : input_matrix_coord, &mat_a, &na, &ma, &vec_a);
        if (!rc)
        {
            if (f != stdin)
                fclose(f);
            printf("Input file name for matrix B. Input stdin if you want to input matrix yourself: ");
            rc = read_matrix(&f, (way_inout == 1) ? input_matrix : input_matrix_coord, &mat_b, &nb, &mb, &vec_b);
            if (!rc)
            {
                if (f != stdin)
                    fclose(f);
                if (na != nb || ma != mb)
                {   
                    printf("Can't sum matrix different sizes\n");
                    rc = ERR_VAL;
                }
                else
                {
                    /*
                    beg = clock();
                    for (size_t i = 0; i < 100; ++i)
                        mat_c = sum_matrix(mat_a, mat_b, na, ma);
                    end = clock();
                    res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0;
                    printf("Matrixes summarize in %.3lf milliseconds\n", res / 100);
                    beg = clock();
                    for (size_t i = 0; i < 100; ++i)
                        vec_c = sum_mat_vectors(vec_a, vec_b);
                    end = clock();
                    res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0;
                    printf("Vectors summarize in %.3lf milliseconds\n", res / 100);
                    */
                    mat_c = sum_matrix(mat_a, mat_b, na, ma);
                    vec_c = sum_mat_vectors(vec_a, vec_b);
                    print_matrix(stdout, mat_c, na, ma);
                    output_vec(stdout, vec_c);
                    
                    free_matrix(mat_c, na);
                    free_vector(vec_c);
                } 

                free_matrix(mat_b, nb);
                free_vector(vec_b);
            }

            free_matrix(mat_a, na);
            free_vector(vec_a);
        }
    }

    return rc;
}