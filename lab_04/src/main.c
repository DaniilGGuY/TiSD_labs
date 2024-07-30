#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "errors.h"
#include "stack_arr.h"
#include "stack_list.h"
#include "process_string.h"

void description()
{
    printf("This program imitate work with stack, which implemented two ways:\n");
    printf("First way - on list, second way - on array\n");
    printf("Stack stores words and print sequences of words in reverse order\n");
    printf("Type 1 to add word in stack\n");
    printf("Type 2 to remove up word from stack\n");
    printf("Type 3 to print array stack\n");
    printf("Type 4 to print list stack\n");
    printf("Type 5 to print result by array stack\n");
    printf("Type 6 to print result by list stack\n");
    printf("Type 0 to leave\n");
}

int main(void)
{
    stack_list_t *list = NULL;
    char arr[N][WORD_LEN + 1], tmp[2];
    size_t size_list = 0, size_arr = 0;
    char str[WORD_LEN + 1];
    int rc = ERR_OK, action;
    bool end_prog = false;
    description();
    while (!rc && !end_prog)
    {
        printf("Enter num of action: ");
        if (scanf("%d", &action) != 1 || action > 6 || action < 0)
        {
            rc = ERR_IO;
            end_prog = true;
            printf("Incorrect action!\n");
        }
        
        if (!rc)
        {
            fgets(tmp, 2, stdin);
            switch (action)
            {
                case 1:
                    printf("Enter a word, which you want to add in stack:\n");
                    rc = read_str(str);
                    if (strlen(str) == 0)
                        rc = ERR_LEN;
                    if (!rc)
                        rc = push_stack_arr(arr, &size_arr, str);
                    else if (rc == ERR_IO)
                        printf("Troubles with reading word\n");
                    else if (rc == ERR_LEN)
                        printf("Incorrect word inputed!\n");
                    if (!rc)
                        rc = push_stack_list(&list, &size_list, str);
                    else if (rc == ERR_OVERFLOW)
                        printf("Stack arr overflow\n");
                    if (!rc)
                        printf("Successfully added!\n");
                    else if (rc == ERR_OVERFLOW)
                        printf("Stack list overflow\n");
                    else if (rc == ERR_MEM)
                        printf("Error with allocate memory\n");
                    break;
                case 2:
                    rc = pop_stack_arr(arr, &size_arr);
                    if (!rc)
                        rc = pop_stack_list(&list, &size_list);
                    else if (rc == ERR_EMPTY)
                        printf("Removing from empty stack\n");
                    if (!rc)
                        printf("Successfully removed!\n");
                    break;
                case 3:
                    if (size_arr == 0)
                        printf("Stack array is empty!\n");
                    else
                        print_stack_arr(arr, size_arr);
                    break;
                case 4:
                    if (size_list == 0)
                        printf("Stack list is empty!\n");
                    else
                        print_stack_list(list);
                    break;
                case 5:
                    if (size_arr == 0)
                        printf("Stack array is empty!\n");
                    else
                        print_res_stack_array(arr, size_arr);
                    break;
                case 6:
                    if (size_list == 0)
                        printf("Stack list is empty!\n");
                    else
                        print_res_stack_list(list);
                    break;
                default:
                    end_prog = true;
                    break;
            }
        }
    }

    if (size_list)
        free_stack_list(list);
    
    size_list = 0;

    return rc;
}