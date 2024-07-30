#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "times.h"

double get_times1(times_t *t)
{
    return (t->maxt1 - t->mint1) * ((double)(rand()) / (double)RAND_MAX) + t->mint1;
}

double get_times2(times_t *t)
{
    return (t->maxt2 - t->mint2) * ((double)(rand()) / (double)RAND_MAX) + t->mint2;
}

double get_times3(times_t *t)
{
    return (t->maxt3 - t->mint3) * ((double)(rand()) / (double)RAND_MAX) + t->mint3;
}

double get_times4(times_t *t)
{
    return (t->maxt4 - t->mint4) * ((double)(rand()) / (double)RAND_MAX) + t->mint4;
}

void edit_times(times_t *t)
{
    bool is = true;
    int action = -1;
    double tech_min, tech_max;

    while (is)
    {
        printf("Type num of time which you want to edit (1, 2, 3 or 4) or 0 if you want to end: ");
        if (scanf("%d", &action) == 1 && action >= 0 && action <= 4)
        {
            is = (action != 0);
            if (action == 1)
            {
                tech_min = t->mint1, tech_max = t->maxt1;
                printf("Input min for T1: ");
                if (scanf("%lf", &t->mint1) == 1)
                {
                    printf("Input max for T1: ");
                    if (scanf("%lf", &t->maxt1) != 1 || t->maxt1 < t->mint1)
                    {
                        t->mint1 = tech_min;
                        t->maxt1 = tech_max;
                        printf("Errors with input max");
                    }
                }
            }
            else if (action == 2)
            {
                tech_min = t->mint2, tech_max = t->maxt2;
                printf("Input min for T2: ");
                if (scanf("%lf", &t->mint2) == 1)
                {
                    printf("Input max for T2: ");
                    if (scanf("%lf", &t->maxt2) != 1 || t->maxt2 < t->mint2)
                    {
                        t->mint2 = tech_min;
                        t->maxt2 = tech_max;
                        printf("Errors with input max");
                    }
                }
            }
            else if (action == 3)
            {
                tech_min = t->mint3, tech_max = t->maxt3;
                printf("Input min for T3: ");
                if (scanf("%lf", &t->mint3) == 1)
                {
                    printf("Input max for T3: ");
                    if (scanf("%lf", &t->maxt3) != 1 || t->maxt3 < t->mint3)
                    {
                        t->mint3 = tech_min;
                        t->maxt3 = tech_max;
                        printf("Errors with input max");
                    }
                }
            }
            else if (action == 4)
            {
                tech_min = t->mint4, tech_max = t->maxt4;
                printf("Input min for T4: ");
                if (scanf("%lf", &t->mint4) == 1)
                {
                    printf("Input max for T4: ");
                    if (scanf("%lf", &t->maxt4) != 1 || t->maxt4 < t->mint4)
                    {
                        t->mint4 = tech_min;
                        t->maxt4 = tech_max;
                        printf("Errors with input max");
                    }
                }
            }
        }
        else
        {
            printf("Incorrect input. Breaking...\n");
            is = false;
        }
    }
}

void print_times(times_t *t)
{
    printf("T1: %lf %lf\n", t->mint1, t->maxt1);
    printf("T2: %lf %lf\n", t->mint2, t->maxt2);
    printf("T3: %lf %lf\n", t->mint3, t->maxt3);
    printf("T4: %lf %lf\n", t->mint4, t->maxt4);
}