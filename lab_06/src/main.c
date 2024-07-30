#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "tree.h"
#include "process.h"
#include "err_codes.h"
#include "tree_node.h"

void description()
{
    printf("This prog allow you to interact with a directory\n");
    printf("of files presented in the form of a tree\n");
}

void menu()
{
    printf("MENU:\n");
    printf("1 - insert in a tree\n");
    printf("2 - delete from a tree\n");
    printf("3 - export in dot file\n");
    printf("4 - carry out task\n");
    printf("5 - pre-order print\n");
    printf("6 - in-order print\n");
    printf("7 - post-order print\n");
    printf("0 - leave from prog\n");
}

tree_t *input_el_for_delete(int act)
{
    int rc, year, month, day, hour, minutes;
    tree_t *elem = NULL;
    char *name = NULL;
    if (act == 1)
    {
        printf("Input name of file, which you want to delete:\n");
        rc = read_str(&name);
    }
    else
    {
        printf("Input date (format Y M D H M) which you want to delete:\n");
        if (scanf("%d %d %d %d %d", &year, &month, &day, &hour, &minutes) != 5)
            rc = ERR_IO;
    }

    if (!rc)
    {
        if (act == 1)
            elem = tree_create(name, NULL, NULL, NULL, 0, 0, 0, 0, 0);
        else
            elem = tree_create(NULL, NULL, NULL, NULL, year, month, day, hour, minutes);
    }

    return elem;
}

tree_t *input_data(int action)
{
    tree_t *input = NULL, *tree = NULL;
    
    char *f1 = strdup("g"), *s1 = strdup("g"), *t1 = strdup("g"), *fr1 = strdup("g");
    input = tree_create(f1, s1, t1, fr1, 8, 8, 8, 8, 8);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f2 = strdup("c"), *s2 = strdup("c"), *t2 = strdup("c"), *fr2 = strdup("c");
    input = tree_create(f2, s2, t2, fr2, 4, 4, 4, 4, 4);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f3 = strdup("h"), *s3 = strdup("h"), *t3 = strdup("h"), *fr3 = strdup("h");
    input = tree_create(f3, s3, t3, fr3, 12, 12, 12, 12, 12);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f4 = strdup("b"), *s4 = strdup("b"), *t4 = strdup("b"), *fr4 = strdup("b");
    input = tree_create(f4, s4, t4, fr4, 2, 2, 2, 2, 2);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f5 = strdup("e"), *s5 = strdup("e"), *t5 = strdup("e"), *fr5 = strdup("e");
    input = tree_create(f5, s5, t5, fr5, 6, 6, 6, 6, 6);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f6 = strdup("gg"), *s6 = strdup("gg"), *t6 = strdup("gg"), *fr6 = strdup("gg");
    input = tree_create(f6, s6, t6, fr6, 10, 10, 10, 10, 10);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f7 = strdup("i"), *s7 = strdup("i"), *t7 = strdup("i"), *fr7 = strdup("i");
    input = tree_create(f7, s7, t7, fr7, 14, 14, 14, 14, 14);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f8 = strdup("a"), *s8 = strdup("a"), *t8 = strdup("a"), *fr8 = strdup("a");
    input = tree_create(f8, s8, t8, fr8, 1, 1, 1, 1, 1);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f9 = strdup("bb"), *s9 = strdup("bb"), *t9 = strdup("bb"), *fr9 = strdup("bb");
    input = tree_create(f9, s9, t9, fr9, 3, 3, 3, 3, 3);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f10 = strdup("cc"), *s10 = strdup("cc"), *t10 = strdup("cc"), *fr10 = strdup("cc");
    input = tree_create(f10, s10, t10, fr10, 5, 5, 5, 5, 5);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f11 = strdup("ee"), *s11 = strdup("ee"), *t11 = strdup("ee"), *fr11 = strdup("ee");
    input = tree_create(f11, s11, t11, fr11, 7, 7, 7, 7, 7);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f12 = strdup("ggg"), *s12 = strdup("ggg"), *t12 = strdup("ggg"), *fr12 = strdup("ggg");
    input = tree_create(f12, s12, t12, fr12, 11, 11, 11, 11, 11);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f13 = strdup("hh"), *s13 = strdup("hh"), *t13 = strdup("hh"), *fr13 = strdup("hh");
    input = tree_create(f13, s13, t13, fr13, 13, 13, 13, 13, 13);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    char *f14 = strdup("k"), *s14 = strdup("k"), *t14 = strdup("k"), *fr14 = strdup("k");
    input = tree_create(f14, s14, t14, fr14, 15, 15, 15, 15, 15);
    tree = tree_insert(tree, input, action == 1 ? cmp_filename : cmp_date);

    return tree;
}

int main()
{
    FILE *f;
    tree_t *tree = NULL, *elem = NULL;
    int rc = OK, action, type_sort, year, month, day, hour, minutes, input;
    char *outfile_name = NULL;
    bool is = true;
    clock_t beg, end;
    description();
    printf("Input 1 if you want to sort by filename or 2 if you want to sort by date:\n");
    if (scanf("%d", &type_sort) != 1 || (type_sort != 1 && type_sort != 2))
        rc = ERR_IO;

    if (!rc)
    {
        printf("Type 1 if you want to input tree automatically and another int val if you don`t want\n");
        if (scanf("%d", &input) != 1)
            rc = ERR_IO;
        else
            if (input == 1)
                tree = input_data(type_sort);
    }

    while (is && !rc)
    {
        menu();
        printf("Input num from range 0-7:\n");
        if (scanf("%d", &action) != 1)
            rc = ERR_IO;
        else
            (void)getc(stdin);

        switch (action)
        {
            case 1:
                rc = read_node(&elem);
                if (!rc)
                {
                    if (!tree_find(tree, elem, type_sort == 1 ? cmp_filename : cmp_date))
                    {
                        beg = clock();
                        tree = tree_insert(tree, elem, type_sort == 1 ? cmp_filename : cmp_date);
                        end = clock();
                        printf("Successfully inserted in %lf mсs\n", (double)(end - beg) / CLOCKS_PER_SEC * 1000.0 * 1000.0);
                    }
                    else
                    {
                        printf("This element already in this tree\n");
                        rc = ERR_INS;
                        tree_free(elem);
                    }
                }
                else
                {
                    if (rc == ERR_IO)
                        printf("Incorrect input. Breaking...\n");
                    else
                        printf("Mem-error\n");
                }

                break;
            case 2:
                if (!tree)
                {
                    printf("Tree is empty!\n");
                    rc = ERR_DEL;
                }
                else
                {
                    elem = input_el_for_delete(type_sort);
                    if (!elem)
                    {
                        printf("Cannot create element\n");
                        rc = ERR_DEL;
                    }
                    else
                    {
                        if (tree_find(tree, elem, type_sort == 1 ? cmp_filename : cmp_date))
                        {
                            beg = clock();
                            tree = tree_delete(tree, elem, type_sort == 1 ? cmp_filename : cmp_date);
                            end = clock();
                            printf("Succesfully deleted in %lf mсs\n", (double)(end - beg) / CLOCKS_PER_SEC * 1000.0 * 1000.0);
                        }
                        else
                        {
                            printf("Cannot find element to delete\n");
                            rc = ERR_DEL;
                        }
                    }
                    tree_free(elem);
                }

                break;
            case 3:
                printf("Input output file name:\n");
                rc = read_str(&outfile_name);
                if (!rc)
                {
                    f = fopen(outfile_name, "w");
                    if (f)
                    {
                        tree_print_dot(f, tree, "outgraph");
                        printf("Successfully printed in file!\n");
                        fclose(f);
                    }
                    else
                        rc = ERR_FILE;

                    free(outfile_name);
                }
                else
                    rc = ERR_FILE;

                break;
            case 4:
                if (!tree)
                    rc = ERR_DEL;
                else
                {
                    printf("Input date (format Y M D H M) under which you want to delete:\n");
                    if (scanf("%d %d %d %d %d", &year, &month, &day, &hour, &minutes) != 5)
                        rc = ERR_IO;
                    if (!rc)
                    {
                        elem = tree_create(NULL, NULL, NULL, NULL, year, month, day, hour, minutes);
                        if (!elem)
                        {
                            printf("Cannot create element\n");
                            rc = ERR_DEL;
                        }
                        else
                        {
                            beg = clock();
                            tree = (type_sort == 1) ? tree_delete_task(tree, elem, cmp_date) : tree_delete_task_sorted(tree, elem, cmp_date);
                            end = clock();
                            printf("Succesfully deleted in %lf mсs\n", (double)(end - beg) / CLOCKS_PER_SEC * 1000.0 * 1000.0);
                        }
                        tree_free(elem);
                    }
                    else
                        printf("Errors with inputing data\n");
                }

                break;
            case 5:
                if (tree)
                    pre_order(tree);
                else
                    printf("Tree is empty\n");

                break;
            case 6:
                if (tree)
                    in_order(tree);
                else
                    printf("Tree is empty\n");

                break;
            case 7:
                if (tree)
                    post_order(tree);
                else
                    printf("Tree is empty\n");

                break;
            case 0:
                printf("Program ended...\n");
                is = false;

                break;
            default:
                rc = ERR_IO;
                break;
        }
    }

    tree_destroy(tree);
    
    return rc;
}