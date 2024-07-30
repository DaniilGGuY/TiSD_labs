#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "err_codes.h"
#include "item.h"
#include "bin_tree.h"
#include "avl_tree.h"
#include "hash_table.h"
#include "process.h"

void discription()
{
    printf("This program simulate work with binary search tree, avl tree and hash table.\n");
    printf("In this program wew try to choose the best one\n");
    printf("In file data/input.txt you can find a list of keywords and their descriptions\n");
    printf("With this data we will work\n");
}

void menu()
{
    printf("1 - if you want to insert in binary search tree\n");
    printf("2 - if you want to insert in avl tree\n");
    printf("3 - if you want to insert in hash table\n");
    printf("4 - if you want to output binary search tree\n");
    printf("5 - if you want to output avl tree\n");
    printf("6 - if you want to output hash table\n");
    printf("7 - if you want to find in binary search tree\n");
    printf("8 - if you want to find in avl tree\n");
    printf("9 - if you want to find in hash table\n");
    printf("0 - if you want to leave\n");
}

int main(void)
{
    FILE *f;
    item_t *item = NULL;
    avl_t *avl = NULL, *el_avl = NULL;
    tree_t *tree = NULL, *el_tree = NULL;
    hash_t *hash = NULL;
    char *outfile_name = NULL, *word = NULL, *discr = NULL;
    bool is = true;
    int rc = OK, action;
    clock_t beg, end;

    discription();
    f = fopen("./data/input.txt", "r");
    if (f)
    {
        rc = read_avl(f, &avl);

        if (!rc)
        {
            rewind(f);
            rc = read_tree(f, &tree);
        }

        if (!rc)
        {
            rewind(f);
            rc = read_hash(f, &hash);
        }

        if (!rc)
            printf("Successfully inputed from file!\n");

        fclose(f);
    }
    else
        rc = ERR_FILE;

    while (is && !rc)
    {
        menu();
        printf("Input num from range 0-9:\n");
        if (scanf("%d", &action) != 1)
            rc = ERR_IO;
        else
            (void)getc(stdin);

        switch (action)
        {
            case 1:
                item = item_create();
                if (!item)
                    rc = ERR_MEM;
                if (!rc)
                    rc = item_input(stdin, item);
                if (!rc)
                    el_tree = tree_create(item);

                if (el_tree)
                {
                    tree = tree_insert(tree, el_tree, item_cmp);
                    el_tree = NULL;
                    printf("Successfully inserted!\n");
                }
                else
                    rc = ERR_MEM;

                break;
            case 2:
                item = item_create();
                if (!item)
                    rc = ERR_MEM;
                if (!rc)
                    rc = item_input(stdin, item);
                if (!rc)
                    el_avl = avl_create(item);

                if (el_avl)
                {
                    avl = avl_insert(avl, el_avl, item_cmp);
                    el_avl = NULL;
                    printf("Successfully inserted!\n");
                }
                else
                    rc = ERR_MEM;

                break;
            case 3:
                item = item_create();
                if (!item)
                    rc = ERR_MEM;
                if (!rc)
                    rc = item_input(stdin, item);

                if (!rc)
                {
                    rc = hash_insert(hash, item);
                    printf("Successfully inserted!\n");
                }
                else
                    rc = ERR_MEM;

                break;
            case 4:
                printf("Input output file name:\n");
                rc = read_str(&outfile_name);
                if (!rc)
                {
                    f = fopen(outfile_name, "w");
                    if (f)
                    {
                        tree_print_dot(f, tree);
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
            case 5:
                printf("Input output file name:\n");
                rc = read_str(&outfile_name);
                if (!rc)
                {
                    f = fopen(outfile_name, "w");
                    if (f)
                    {
                        avl_print_dot(f, avl);
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
            case 6:
                printf("Input output file name:\n");
                rc = read_str(&outfile_name);
                if (!rc)
                {
                    f = fopen(outfile_name, "w");
                    if (f)
                    {
                        hash_print(f, hash);
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
            case 7:
                printf("Input key word:\n");
                item = item_create();
                if (!item)
                    rc = ERR_MEM;
                if (!rc)
                    rc = read_str(&item->word);
                if (!rc)
                    el_tree = tree_create(item);

                if (el_tree)
                {
                    /*beg = clock();
                    tree_t *found = NULL;
                    for (size_t i = 0; i < 1000000; ++i)
                        found = tree_find(tree, el_tree, item_cmp);
                    end = clock();
                    printf("Time: %lf\n", (double)(end - beg) / CLOCKS_PER_SEC);*/
                    tree_t *found = tree_find(tree, el_tree, item_cmp);
                    if (found)
                    {
                        printf("Successfully found!\n");
                        printf("Key: %s\nValue: %s\n", found->item->word, found->item->description);
                    }
                    else
                        printf("Not found\n");

                    tree_free(el_tree);
                }
                else
                    rc = ERR_MEM;

                break;
            case 8:
                printf("Input key word:\n");
                item = item_create();
                if (!item)
                    rc = ERR_MEM;
                if (!rc)
                    rc = read_str(&item->word);
                if (!rc)
                    el_avl = avl_create(item);

                if (el_avl)
                {
                    /*beg = clock();
                    avl_t *found = NULL;
                    for (size_t i = 0; i < 1000000; ++i)
                        found = avl_find(avl, el_avl, item_cmp);
                    end = clock();
                    printf("Time: %lf\n", (double)(end - beg) / CLOCKS_PER_SEC);*/
                    avl_t *found = avl_find(avl, el_avl, item_cmp);
                    if (found)
                    {
                        printf("Successfully found!\n");
                        printf("Key: %s\nValue: %s\n", found->item->word, found->item->description);
                    }
                    else
                        printf("Not found\n");
                    
                    avl_free(el_avl);
                }
                else
                    rc = ERR_MEM;

                break;
            case 9:
                printf("Input key word:\n");
                rc = read_str(&word);
                if (!rc)
                {
                    /*beg = clock();
                    for (size_t i = 0; i < 1000000; ++i)
                        discr = hash_find2(hash, word);
                    end = clock();
                    printf("Time: %lf\n", (double)(end - beg) / CLOCKS_PER_SEC);*/
                    discr = hash_find2(hash, word);
                    if (discr)
                    {
                        printf("Successfully found!\n");
                        printf("Key: %s\nValue: %s\n", word, discr);
                    }
                    else
                        printf("Not found\n");
                    
                    free(word);
                }
                else
                    rc = ERR_MEM;

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

    if (tree)
        tree_destroy(tree);
    if (avl)
        avl_destroy(avl);
    if (hash)
        hash_free(hash);

    return rc;
}