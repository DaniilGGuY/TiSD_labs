#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "list.h"
#include "array.h"
#include "times.h"
#include "process.h"
#include "errors.h"

void description()
{
    printf("This program can performs the work simulation process with your params\n");
    printf("Program allowed to solve task with two methods: queue on array and queue on list\n");
    printf("There is two queues. Each of queues has two params: times of sending requests\n");
    printf("and time of process requests\n");
    printf("Lets try!\n");
}

int main(void)
{    
    srand(time(NULL));
    times_t t = { .mint1 = 1, .maxt1 = 5, .mint2 = 0, .maxt2 = 3, .mint3 = 0, .maxt3 = 4, .mint4 = 0, .maxt4 = 1 };
    times_t *pt = &t;
    array_t data_1 = { .head = -1, .tail = -1 }, data_2 = { .head = -1, .tail = -1 };
    array_t *q_1 = &data_1, *q_2 = &data_2;

    int action, rc = OK;
    bool is = true;

    description();
    while (is && !rc)
    {
        menu();
        printf("Input num from range 0-4:\n");
        if (scanf("%d", &action) != 1)
            rc = ERR_IO;

        switch (action)
        {
            case 1:
                process_list(pt);
                break;
            case 2:
                process_array(pt, q_1, q_2);
                break;
            case 3:
                printf("Now params:\n");
                print_times(pt);
                edit_times(pt);
                printf("New params:\n");
                print_times(pt);
                break;
            case 4:
                printf("Results by 1000 measurements for list-queue:\n");
                research_list();
                printf("Results by 1000 measurements for array-queue:\n");
                research_array();
                break;
            case 0:
                printf("Program ended...\n");
                is = false;
                break;
            default:
                printf("Input num from range 0-4:\n");
                break;
        }
    }

    return rc;
}