#include <stdlib.h>
#include <stdio.h>
#include "priorityqueue.h"

typedef struct
{
    int i;
    char c;
} testData;

int compareTestData(void *a, void *b)
{
    testData *ta = (testData *)a;
    testData *tb = (testData *)b;
    return ta->i - tb->i;
}

void printTestData(void *data)
{
    printf("data i = %i\n", *(testData *)data);
}

int testPriorityQueue()
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

    return isError;
}