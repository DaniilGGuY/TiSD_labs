#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "array.h"
#include "process.h"
#include "errors.h"

#define EPS     1e-8

void menu()
{
    printf("Type 1 to imitate task with list-queue\n");
    printf("Type 2 to imitate task with array-queue\n");
    printf("Type 3 to edit values of times\n");
    printf("Type 4 to calculate times of work push and pop operations of queues (microseconds)\n");
    printf("Type 0 to end program\n");
    printf("Enter action:\n");
}

void process_list(times_t *pt)
{
    list_t *q_1 = lqueue_create(), *q_2 = lqueue_create();
    if (!q_2 || !q_1)
    {
        if (q_1)
            lqueue_destroy(q_1);
        if (q_2)
            lqueue_destroy(q_2);

        printf("Cannot simulate list-queue. Error mem\n");
        return;
    }

    printf("Input 1 if you want to print adresses:\n");
    int act = 0;
    scanf("%d", &act);

    bool is_first = true, flag = true;
    size_t len_1 = 0, len_2 = 0, in_1 = 0, in_2 = 0, out_1 = 0, out_2 = 0;
    double time_in_1 = 0.0, time_out_1, time_in_2 = 0.0, time_out_2, el, now_time = 0.0;
    double av_time_work1 = (pt->maxt1 + pt->mint1) / 2, av_time_work2 = (pt->maxt2 + pt->mint2) / 2;
    double work_1 = 0.0, work_2 = 0.0;
    double out_t1, out_t2;
    double beg, end, res;
    beg = clock();
    while (out_1 < 1000 && len_1 < N * 10 && len_2 < N * 10)
    {
        if (is_first)
        {
            if (lqueue_is_empty(q_1))
            {
                if (fabs(time_in_1 - time_in_2) < EPS || time_in_1 - time_in_2 < 0)
                {
                    (void)lqueue_push(q_1, time_in_1);
                    if (act == 1)
                        printf("alloc q1 %p\n", (void *)q_1->tail);
                    in_1 += 1;
                    len_1 += 1;
                    now_time = time_in_1;
                    out_t1 = get_times3(pt);
                    time_out_1 = time_in_1 + out_t1;
                    work_1 += out_t1;
                    time_in_1 = time_in_1 + get_times1(pt);
                }
                else
                    is_first = false;
            }
            else
            {
                if ((fabs(time_in_1 - time_in_2) < EPS || time_in_1 - time_in_2 < 0) && (fabs(time_in_1 - time_out_1) < EPS || time_in_1 - time_out_1 < 0))
                {
                    (void)lqueue_push(q_1, time_in_1);
                    if (act == 1)
                        printf("alloc q1 %p\n", (void *)q_1->tail);
                    in_1 += 1;
                    len_1 += 1;
                    now_time = time_in_1;
                    time_in_1 = time_in_1 + get_times1(pt);
                }
                else if ((fabs(time_out_1 - time_in_2) < EPS || time_out_1 - time_in_2 < 0) && (fabs(time_in_1 - time_out_1) < EPS || time_out_1 - time_in_1 < 0))
                {
                    if (act == 1)
                        printf("free q1 %p\n", (void *)q_1->head);
                    (void)lqueue_pop(q_1, &el);
                    out_1 += 1;
                    len_1 -= 1;
                    now_time = time_out_1;
                    if (!lqueue_is_empty(q_1))
                    {
                        out_t1 = get_times3(pt);
                        time_out_1 = now_time + out_t1;
                        work_1 += out_t1;
                    }
                    flag = true;
                }
                else
                {
                    (void)lqueue_push(q_2, time_in_2);
                    if (act == 1)
                        printf("alloc q2 %p\n", (void *)q_2->tail);
                    in_2 += 1;
                    len_2 += 1;
                    now_time = time_in_2;
                    time_in_2 = time_in_2 + get_times2(pt);
                }
            }
        }
        else
        {
            if (lqueue_is_empty(q_2))
            {
                if (fabs(time_in_1 - time_in_2) < EPS || time_in_2 - time_in_1 < 0)
                {
                    (void)lqueue_push(q_2, time_in_2);
                    if (act == 1)
                        printf("alloc q2 %p\n", (void *)q_2->tail);
                    in_2 += 1;
                    len_2 += 1;
                    now_time = time_in_2;
                    out_t2 = get_times4(pt);
                    time_out_2 = time_in_2 + out_t2;
                    work_2 += out_t2;
                    time_in_2 = time_in_2 + get_times2(pt);
                }
                else
                    is_first = true;
            }
            else
            {
                if ((fabs(time_in_1 - time_in_2) < EPS || time_in_2 - time_in_1 < 0) && (fabs(time_in_2 - time_out_2) < EPS || time_in_2 - time_out_2 < 0))
                {
                    (void)lqueue_push(q_2, time_in_2);
                    if (act == 1)
                        printf("alloc q2 %p\n", (void *)q_2->tail);
                    in_2 += 1;
                    len_2 += 1;
                    now_time = time_in_2;
                    time_in_2 = time_in_2 + get_times2(pt);
                }
                else if ((fabs(time_out_2 - time_in_1) < EPS || time_out_2 - time_in_1 < 0) && (fabs(time_in_2 - time_out_2) < EPS || time_out_2 - time_in_2 < 0))
                {
                    if (act == 1)
                        printf("free q2 %p\n", (void *)q_2->head);
                    (void)lqueue_pop(q_2, &el);
                    out_2 += 1;
                    len_2 -= 1;
                    now_time = time_out_2;
                    if (!lqueue_is_empty(q_2))
                    {
                        out_t2 = get_times4(pt);
                        time_out_2 = now_time + out_t2;
                        work_2 += out_t2;
                    }
                    flag = true;
                }
                else
                {
                    (void)lqueue_push(q_1, time_in_1);
                    if (act == 1)
                        printf("alloc q1 %p\n", (void *)q_1->tail);
                    in_1 += 1;
                    len_1 += 1;
                    now_time = time_in_1;
                    time_in_1 = time_in_1 + get_times1(pt);
                }
            }
        }

        if ((out_1 + out_2) % 100 == 0 && flag)
        {
            printf("\n\nReport for %zu numbers of requests\n", out_1 + out_2);
            printf("First queue in: %zu\n", in_1);
            printf("First queue out: %zu\n", out_1);
            printf("First queue len: %zu\n", len_1);
            printf("Second queue in: %zu\n", in_2);
            printf("Second queue out: %zu\n", out_2);
            printf("Second queue len: %zu\n", len_2);
            flag = false;
        }
    }
    end = clock();

    if (len_1 == N || len_2 == N)
    {
        printf("Queue overflow\n");
        lqueue_destroy(q_1);
        lqueue_destroy(q_2);
        return;
    }

    double theor_fstq = in_1 * av_time_work1, theor_secq = in_2 * av_time_work2;
    double theor_mod = (theor_fstq > theor_secq) ? theor_fstq : theor_secq;
    printf("\n\nTotal simulation time: %lf\n", now_time);
    printf("Time wasting: %lf\n", now_time - work_1 - work_2);
    printf("Theoretical time-modeling: %lf\n", theor_mod);
    printf("Error time-modeling: %lf%%\n", fabs(100 * (now_time - theor_mod) / theor_mod));
    printf("First queue in: %zu\n", in_1);
    printf("First queue out: %zu\n", out_1);
    printf("First queue len: %zu\n", len_1);
    printf("First queue work: %lf\n", work_1);
    printf("Second queue in: %zu\n", in_2);
    printf("Second queue out: %zu\n", out_2);
    printf("Second queue len: %zu\n", len_2);
    printf("Second queue work: %lf\n", work_2);

    lqueue_destroy(q_1);
    lqueue_destroy(q_2);

    res = (end - beg) / CLOCKS_PER_SEC * 1000.0;
    printf("\n\nTime of work prog: %lf\n\n", res);
}

void process_array(times_t *pt, array_t *q_1, array_t *q_2)
{
    if (!q_2 || !q_1)
    {
        printf("Cannot simulate array-queue. Error mem\n");
        return;
    }

    bool is_first = true, flag = true;
    size_t len_1 = 0, len_2 = 0, in_1 = 0, in_2 = 0, out_1 = 0, out_2 = 0;
    double time_in_1 = 0.0, time_out_1, time_in_2 = 0.0, time_out_2, el, now_time = 0.0;
    double av_time_work1 = (pt->maxt1 + pt->mint1) / 2, av_time_work2 = (pt->maxt2 + pt->mint2) / 2;
    double work_1 = 0.0, work_2 = 0.0;
    double out_t1, out_t2;
    double beg, end, res;
    beg = clock();
    while (out_1 < 1000 && len_1 < N * 10 && len_2 < N * 10)
    {
        //printf("TEST %zu %zu\n", len_1, len_2);
        if (is_first)
        {
            if (aqueue_is_empty(q_1))
            {
                if (fabs(time_in_1 - time_in_2) < EPS || time_in_1 - time_in_2 < 0)
                {
                    (void)aqueue_push(q_1, time_in_1);
                    in_1 += 1;
                    len_1 += 1;
                    now_time = time_in_1;
                    out_t1 = get_times3(pt);
                    time_out_1 = time_in_1 + out_t1;
                    work_1 += out_t1;
                    time_in_1 = time_in_1 + get_times1(pt);
                }
                else
                    is_first = false;
            }
            else
            {
                if ((fabs(time_in_1 - time_in_2) < EPS || time_in_1 - time_in_2 < 0) && (fabs(time_in_1 - time_out_1) < EPS || time_in_1 - time_out_1 < 0))
                {
                    (void)aqueue_push(q_1, time_in_1);
                    in_1 += 1;
                    len_1 += 1;
                    now_time = time_in_1;
                    time_in_1 = time_in_1 + get_times1(pt);
                }
                else if ((fabs(time_out_1 - time_in_2) < EPS || time_out_1 - time_in_2 < 0) && (fabs(time_in_1 - time_out_1) < EPS || time_out_1 - time_in_1 < 0))
                {
                    (void)aqueue_pop(q_1, &el);
                    out_1 += 1;
                    len_1 -= 1;
                    now_time = time_out_1;
                    if (!aqueue_is_empty(q_1))
                    {
                        out_t1 = get_times3(pt);
                        time_out_1 = now_time + out_t1;
                        work_1 += out_t1;
                    }
                    flag = true;
                }
                else
                {
                    (void)aqueue_push(q_2, time_in_2);
                    in_2 += 1;
                    len_2 += 1;
                    now_time = time_in_2;
                    time_in_2 = time_in_2 + get_times2(pt);
                }
            }
        }
        else
        {
            if (aqueue_is_empty(q_2))
            {
                if (fabs(time_in_1 - time_in_2) < EPS || time_in_2 - time_in_1 < 0)
                {
                    (void)aqueue_push(q_2, time_in_2);
                    in_2 += 1;
                    len_2 += 1;
                    now_time = time_in_2;
                    out_t2 = get_times4(pt);
                    time_out_2 = time_in_2 + out_t2;
                    work_2 += out_t2;
                    time_in_2 = time_in_2 + get_times2(pt);
                }
                else
                    is_first = true;
            }
            else
            {
                if ((fabs(time_in_1 - time_in_2) < EPS || time_in_2 - time_in_1 < 0) && (fabs(time_in_2 - time_out_2) < EPS || time_in_2 - time_out_2 < 0))
                {
                    (void)aqueue_push(q_2, time_in_2);
                    in_2 += 1;
                    len_2 += 1;
                    now_time = time_in_2;
                    time_in_2 = time_in_2 + get_times2(pt);
                }
                else if ((fabs(time_out_2 - time_in_1) < EPS || time_out_2 - time_in_1 < 0) && (fabs(time_in_2 - time_out_2) < EPS || time_out_2 - time_in_2 < 0))
                {
                    (void)aqueue_pop(q_2, &el);
                    out_2 += 1;
                    len_2 -= 1;
                    now_time = time_out_2;
                    if (!aqueue_is_empty(q_2))
                    {
                        out_t2 = get_times4(pt);
                        time_out_2 = now_time + out_t2;
                        work_2 += out_t2;
                    }
                    flag = true;
                }
                else
                {
                    (void)aqueue_push(q_1, time_in_1);
                    in_1 += 1;
                    len_1 += 1;
                    now_time = time_in_1;
                    time_in_1 = time_in_1 + get_times1(pt);
                }
            }
        }

        if ((out_1 + out_2) % 100 == 0 && flag)
        {
            printf("\n\nReport for %zu numbers of requests\n", out_1 + out_2);
            printf("First queue in: %zu\n", in_1);
            printf("First queue out: %zu\n", out_1);
            printf("First queue len: %zu\n", len_1);
            printf("Second queue in: %zu\n", in_2);
            printf("Second queue out: %zu\n", out_2);
            printf("Second queue len: %zu\n", len_2);
            flag = false;
        }
    }
    end = clock();

    if (len_1 == N || len_2 == N)
    {
        q_1->head = -1, q_1->tail = -1, q_2->head = -1, q_2->tail = -1;
        printf("Queue overflow\n");
        return;
    }

    double theor_fstq = in_1 * av_time_work1, theor_secq = in_2 * av_time_work2;
    double theor_mod = (theor_fstq > theor_secq) ? theor_fstq : theor_secq;
    printf("\n\nTotal simulation time: %lf\n", now_time);
    printf("Time wasting: %lf\n", now_time - work_1 - work_2);
    printf("Theoretical time-modeling: %lf\n", theor_mod);
    printf("Error time-modeling: %lf%%\n", fabs(100 * (now_time - theor_mod) / theor_mod));
    printf("First queue in: %zu\n", in_1);
    printf("First queue out: %zu\n", out_1);
    printf("First queue len: %zu\n", len_1);
    printf("First queue work: %lf\n", work_1);
    printf("Second queue in: %zu\n", in_2);
    printf("Second queue out: %zu\n", out_2);
    printf("Second queue len: %zu\n", len_2);
    printf("Second queue work: %lf\n", work_2);
    q_1->head = -1, q_1->tail = -1, q_2->head = -1, q_2->tail = -1;

    res = (end - beg) / CLOCKS_PER_SEC * 1000.0;
    printf("\n\nTime of work prog: %lf\n\n", res);
}

void research_list()
{
    list_t *q = lqueue_create();
    if (!q)
    {
        printf("Cannot calc time for list-queue. Error mem\n");
        return;
    }

    double beg, end, res, el;
    int rc = OK;
    beg = clock();
    for (size_t i = 0; i < N && !rc; ++i)
        rc = lqueue_push(q, (double)i);
    end = clock();
    if (rc)
    {
        lqueue_destroy(q);
        printf("Cannot calc time for list-queue. Error mem\n");
        return;
    }

    res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0 * 1000.0 / N;
    printf("Push: %lf\n", res);

    beg = clock();
    for (size_t i = 0; i < N && !rc; ++i)
        rc = lqueue_pop(q, &el);
    end = clock();
    if (rc)
    {
        lqueue_destroy(q);
        printf("Cannot calc time for list-queue. Error mem\n");
        return;
    }

    res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0 * 1000.0 / N;
    printf("Pop: %lf\n", res);

    lqueue_destroy(q);
}

void research_array()
{
    array_t *q, data = { .head = -1, .tail = -1};
    q = &data;

    double beg, end, res, el;
    int rc = OK;
    beg = clock();
    for (size_t i = 0; i < N && !rc; ++i)
        rc = aqueue_push(q, (double)i);
    end = clock();
    if (rc)
    {
        printf("Cannot calc time for array-queue. Error mem\n");
        return;
    }

    res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0 * 1000.0 / N;
    printf("Push: %lf\n", res);

    beg = clock();
    for (size_t i = 0; i < N && !rc; ++i)
        rc = aqueue_pop(q, &el);
    end = clock();
    if (rc)
    {
        printf("Cannot calc time for array-queue. Error mem\n");
        return;
    }

    res = (double)(end - beg) / CLOCKS_PER_SEC * 1000.0 * 1000.0 / N;
    printf("Pop: %lf\n", res);
}
