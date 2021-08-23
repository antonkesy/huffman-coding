#include <stdlib.h>
#include <stdio.h>
#include "priorityqueue.h"
#include "priorityqueuetest.h"

#define SIZE_TEST_AMOUNT 100

int compareTestData(const void *a, const void *b)
{
    testData *ta = (testData *)a;
    testData *tb = (testData *)b;
    return ta->i - tb->i;
}

void printTestData(void *data)
{
    printf("data i = %i\n", *(int *)data);
}

int test1()
{
    int isError = 0;
    priorityque *pq = createPQ(compareTestData);
    if (isEmpty(pq) != true)
    {
        isError = 1;
    }
    testData *data = (testData *)malloc(sizeof(testData) * 5);
    for (int i = 0; i < 5; ++i)
    {
        data[i].i = i;
        void *vData = &(data[i]);
        push(pq, vData);
    }

    if (isEmpty(pq) != false)
    {
        isError = 1;
    }

    if (pq->size != 5)
    {
        isError = 1;
    }
    testData *first = (testData *)pop(pq);

    if (first->i != 0)
    {
        isError = 1;
    }

    testData *second = (testData *)pop(pq);

    if (second->i != 1)
    {
        isError = 1;
    }

    push(pq, first);
    testData *small = (testData *)malloc(sizeof(testData));
    small->i = -1;
    push(pq, small);
    push(pq, first);
    testData two = {2, 12};
    push(pq, &two);

    //printf("iterat:\n");
    //iterate(pq, printTestData);

    //TODO free memory
    return isError;
}

int compareInt(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

void printInt(void *data)
{
    printf("%i\n", *(int *)data);
}

int test2()
{
    //TODO automate test
    int isError = 0;
    priorityque *pq = createPQ(compareInt);

    int a = 5;
    int b = 1;
    int c = 3;
    int d = 6;
    int e = 0;

    push(pq, &a);
    push(pq, &b);
    push(pq, &c);
    push(pq, &d);
    push(pq, &e);

    iterate(pq, printInt);
    printf("\n");
    pop(pq);
    pop(pq);
    iterate(pq, printInt);
    printf("\n");
    push(pq, &a);
    push(pq, &e);
    iterate(pq, printInt);

    clear(pq);
    if (pq->size != 0)
    {
        isError = 1;
    }
    delete (pq);

    if (pq != NULL)
    {
        isError = 1;
    }

    return isError;
}

int testSizePush()
{
    int isError = 0;
    priorityque *pq = createPQ(compareInt);

    if (pq->size != 0)
    {
        isError = 1;
    }

    int numbers[SIZE_TEST_AMOUNT];
    for (register size_t i = 0U; i < SIZE_TEST_AMOUNT; ++i)
    {
        numbers[i] = SIZE_TEST_AMOUNT - i;
        push(pq, &numbers[i]);
        if (pq->size != (i + 1))
        {
            isError = 1;
        }
    }

    for (register int i = SIZE_TEST_AMOUNT - 1; i >= 0; --i)
    {
        int value = *((int *)pop(pq));
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

int testPriorityQueue()
{
    int isError = test1();
    //isError = test2();
    isError = testSizePush();
    return isError;
}