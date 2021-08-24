#include "minheaptest.h"
#include "minheap.h"
#include <stdio.h>

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

    return 0;
}