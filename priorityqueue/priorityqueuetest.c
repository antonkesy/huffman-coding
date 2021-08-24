#include <stdlib.h>
#include <stdio.h>
#include "priorityqueue.h"
#include "priorityqueuetest.h"

#define SIZE_TEST_AMOUNT 100

int _compare_test_data(const void *a, const void *b)
{
    testData *ta = (testData *)a;
    testData *tb = (testData *)b;
    return ta->i - tb->i;
}

void print_test_data(void *data)
{
    printf("data i = %i\n", *(int *)data);
}

int test_1()
{
    int isError = 0;
    priorityque *pq = create_priority_que(_compare_test_data);
    if (is_empty_priority_que(pq) != true)
    {
        isError = 1;
    }
    testData *data = (testData *)malloc(sizeof(testData) * 5);
    for (int i = 0; i < 5; ++i)
    {
        data[i].i = i;
        void *vData = &(data[i]);
        push_priority_que(pq, vData);
    }

    if (is_empty_priority_que(pq) != false)
    {
        isError = 1;
    }

    if (pq->size != 5)
    {
        isError = 1;
    }
    testData *first = (testData *)pop_priority_que(pq);

    if (first->i != 0)
    {
        isError = 1;
    }

    testData *second = (testData *)pop_priority_que(pq);

    if (second->i != 1)
    {
        isError = 1;
    }

    push_priority_que(pq, first);
    testData *small = (testData *)malloc(sizeof(testData));
    small->i = -1;
    push_priority_que(pq, small);
    push_priority_que(pq, first);
    testData two = {2, 12};
    push_priority_que(pq, &two);

    //printf("iterat:\n");
    //iterate(pq, print_test_data);

    //TODO free memory
    return isError;
}

int _compare_int(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

void print_test_data_int(void *data)
{
    printf("%i\n", *(int *)data);
}

int test_2()
{
    int isError = 0;
    priorityque *pq = create_priority_que(_compare_int);

    int a = 5;
    int b = 1;
    int c = 3;
    int d = 6;
    int e = 0;

    push_priority_que(pq, &a);
    push_priority_que(pq, &b);
    push_priority_que(pq, &c);
    push_priority_que(pq, &d);
    push_priority_que(pq, &e);

    iterate_priority_que(pq, print_test_data_int);
    printf("\n");
    pop_priority_que(pq);
    pop_priority_que(pq);
    iterate_priority_que(pq, print_test_data_int);
    printf("\n");
    push_priority_que(pq, &a);
    push_priority_que(pq, &e);
    iterate_priority_que(pq, print_test_data_int);

    clear_priority_que(pq);
    if (pq->size != 0)
    {
        isError = 1;
    }
    delete_priority_que(pq);

    if (pq != NULL)
    {
        isError = 1;
    }

    return isError;
}

int test_size_push()
{
    int isError = 0;
    priorityque *pq = create_priority_que(_compare_int);

    if (pq->size != 0)
    {
        isError = 1;
    }

    int numbers[SIZE_TEST_AMOUNT];
    for (register size_t i = 0U; i < SIZE_TEST_AMOUNT; ++i)
    {
        numbers[i] = SIZE_TEST_AMOUNT - i;
        push_priority_que(pq, &numbers[i]);
        if (pq->size != (i + 1))
        {
            isError = 1;
        }
    }

    for (register int i = SIZE_TEST_AMOUNT - 1; i >= 0; --i)
    {
        int value = *((int *)pop_priority_que(pq));
        if (pq->size != (i + 1) && value != SIZE_TEST_AMOUNT - i)
        {
            isError = 1;
        }
    }

    if (pq->size != 0)
    {
        isError = 1;
    }

    return isError;
}

int test_priority_queue()
{
    int isError = test_1();
    //isError = test_2();
    isError = test_size_push();
    return isError;
}