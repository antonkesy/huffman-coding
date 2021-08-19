#ifndef PRIOTRITYQUEUETEST_H
#define PRIOTRITYQUEUETEST_H

typedef struct
{
    int i;
    char c;
} testData;

int testPriorityQueue();

int test1();
int compareTestData(const void *a, const void *b);
void printTestData(void *data);

int test2();
int compareInt(const void *a, const void *b);
void printInt(void *data);

#endif
