#ifndef PRIOTRITYQUEUETEST_H
#define PRIOTRITYQUEUETEST_H

typedef struct
{
    int i;
    char c;
} testData;

int test_priority_queue();

int test_1();
int _compare_test_data(const void *a, const void *b);
void print_test_data(void *data);

int test_2();
int _compare_int(const void *a, const void *b);
void print_test_data_int(void *data);

int testSizePush();

#endif
