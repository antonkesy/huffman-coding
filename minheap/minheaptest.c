#include "minheaptest.h"
#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>

int test_min_heap()
{
    minheap *mh = create_min_heap(10);
    int ia = 73;
    heapdata *a = create_heap_data(3, &ia);
    insert(mh, a);

    int ic = 42;
    heapdata *c = create_heap_data(1, &ic);
    insert(mh, c);

    int ib = 66;
    heapdata *b = create_heap_data(6, &ib);
    insert(mh, b);

    printf("%i\t%i\n", get_key(mh, 0), *(int *)get_data(mh, 0));
    printf("%i\t%i\n", get_key(mh, 1), *(int *)get_data(mh, 1));
    printf("%i\t%i\n", get_key(mh, 2), *(int *)get_data(mh, 2));
    printf("%i\n", extract_min(mh)->key);
    printf("%i\n", extract_min(mh)->key);

    free(a);
    free(b);
    free(c);
    free(mh);

    return 0;
}

int heap_test_range()
{

    minheap *mh = create_min_heap(100);
    int *numbers = malloc(sizeof(int) * 100);

    for (int i = 0; i < 100; ++i)
    {
        numbers[i] = 100 - i;
        insert(mh, create_heap_data(numbers[i], &numbers[i]));
    }
    //print_min_heap(mh);

    for (int i = 0; i < 100; ++i)
    {
        printf("%i\t", extract_min(mh)->key);
    }

    free(mh);

    return 0;
}