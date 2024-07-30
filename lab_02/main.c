#include <stdio.h>
#include <stdbool.h>
#include "error.h"
#include "table.h"
#include "table_funcs.h"
#include "constant.h"
#include "stud_funcs.h"

void print_menu()
{
    printf("Select an action. Write int num\n");
    printf("1 - upload file with table\n");
    printf("2 - print table\n");
    printf("3 - print table via table keys\n");
    printf("4 - add row in table\n");
    printf("5 - delete row from table\n");
    printf("6 - sort table\n");
    printf("7 - sort table via table keys\n");
    printf("8 - filtered search by year of admission and home-place = rental home\n");
    printf("0 - if you want to exit\n");
    printf("Your choiсе: ");
}

int check_file(FILE **f, char *mods)
{
    char str[FILE_NAME + 1];
    int rc = ERR_OK;
    if (scanf("%s", str) != 1)
        rc = ERR_IO;
    else
    {
        *f = fopen(str, mods);
        if (!(*f))
            rc = ERR_FILE;
    }
    
    return rc;
}

int check_choice(int *num)
{
    int rc = ERR_OK;
    if (scanf("%d", num) != 1)
        rc = ERR_IO;

    if (*num > 8 || *num < 0)
        rc = ERR_IO;

    return rc;
}

int main(void)
{
    FILE *f;
    student_t table[N];
    key_field_t keys[N];
    size_t table_len = 0, year_of_adm;
    int rc = ERR_OK, choice, str_del_num, choice_sort;
    bool end_prog = false;

    printf("This program stores a table with student information.\n");
    printf("You can sort this table by student surname.\n");
    while (true)
    {
        if (end_prog)
            break;

        print_menu();

        while (check_choice(&choice)) 
            printf("ERROR. Input num in range [0;8]\nYour choice: ");

        switch (choice)
        {
            case 1:
                printf("Write in-file name: ");
                rc = check_file(&f, "r");
                if (!rc)
                {
                    rc = upload_table(f, table, &table_len);
                    if (rc)
                    {
                        end_prog = true;
                        printf("ERROR. Incorrect format of input\n");
                    }

                    fclose(f);
                } 
                else
                {
                    end_prog = true;
                    printf("ERROR. Cannot open file with this name\n");
                }
                break;
            case 2:
                if (table_len == 0)
                {
                    printf("ERROR. Nothing to output\n");
                    rc = ERR_IO;
                }
                if (!rc)
                {
                    printf("Write out-file name: ");
                    rc = check_file(&f, "w");
                    if (!rc)
                    {
                        print_table(f, table, table_len);
                        fclose(f);
                    } 
                    else
                    {
                        end_prog = true;
                        printf("ERROR. Cannot open file with this name\n");
                    }
                }
                break;
            case 3:
                if (table_len == 0)
                {
                    printf("ERROR. Nothing to output\n");
                    rc = ERR_IO;
                }
                if (!rc)
                {
                    printf("Write out-file name: ");
                    rc = check_file(&f, "w");
                    if (!rc)
                    {
                        print_table_by_keys(f, table, keys, table_len);
                        fclose(f);
                    } 
                    else
                    {
                        end_prog = true;
                        printf("ERROR. Cannot open file with this name\n");
                    }
                }
                break;
            case 4:
                printf("Input info about student in a row:\n");
                rc = add_row(table, &table_len);
                if (rc == ERR_OVERFLOW)
                {
                    end_prog = true;
                    printf("ERROR. Cannot add new row. Overflow\n");
                }
                else if (rc)
                {
                    end_prog = true;
                    printf("ERROR. Incorrect input\n");
                }
                break;  
            case 5:
                printf("Input num string in table which you want to delete: ");
                if (scanf("%d", &str_del_num) != 1)
                {
                    end_prog = true;
                    printf("ERROR. Input incorrect int val\n");
                    rc = ERR_IO;
                }

                rc = delete_row(table, &table_len, str_del_num);
                if (rc)
                {
                    end_prog = true;
                    printf("ERROR. Cannot delete string with this index\n");
                }
                break;
            case 6:
                if (table_len != 0)
                {
                    printf("Choose algorithm of sort\n");
                    printf("Input 1 if you want to use bubble sort\n");
                    printf("or 2 if you want to use qsort\n");
                    printf("Your choice: ");
                    while (scanf("%d", &choice_sort) != 1 && (choice_sort > 2 || choice_sort < 1))
                        printf("Input 1 or 2\n");
                    if (choice_sort == 1)
                        bubble_sort_table(table, table_len);
                    else
                        qsort_table(table, table_len);
                    print_table(stdout, table, table_len);
                    printf("Successfully!\n");
                    f = fopen("out.txt", "w");
                    print_table(f, table, table_len);
                    fclose(f);
                }
                else
                {
                    printf("ERROR. Nothing to sort\n");
                    rc = ERR_IO;
                }
                break;
            case 7:
                if (table_len != 0)
                {
                    printf("Choose algorithm of sort\n");
                    printf("Input 1 if you want to use bubble sort\n");
                    printf("or 2 if you want to use qsort\n");
                    printf("Your choice: ");
                    while (scanf("%d", &choice_sort) != 1 && (choice_sort > 2 || choice_sort < 1))
                        printf("Input 1 or 2\n");
                    create_table_keys(table, keys, table_len);
                    print_table_keys(keys, table_len);
                    printf("\n");
                    if (choice_sort == 1)
                        bubble_sort_table_keys(keys, table_len);
                    else
                        qsort_table_keys(keys, table_len);
                    print_table_by_keys(stdout, table, keys, table_len);
                    printf("Successfully!\n");
                    print_table_keys(keys, table_len);
                    f = fopen("out.txt", "w");
                    print_table_by_keys(f, table, keys, table_len);
                    fclose(f);
                }
                else
                {
                    printf("ERROR. Nothing to sort\n");
                    rc = ERR_IO;
                }
                break;
            case 8:
                if (table_len != 0)
                {
                    printf("Input year of admission: ");
                    if (scanf("%zu", &year_of_adm) != 1)
                        rc = ERR_IO;
                    if (!rc)
                        filter_output(table, table_len, year_of_adm);
                }
                else
                {
                    printf("ERROR. No one note\n");
                    rc = ERR_IO;
                }
                break;
            default:
                end_prog = true;
                break;
        }
    }

    return rc;
}