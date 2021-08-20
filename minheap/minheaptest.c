#include "minheaptest.h"
#include "minheap.h"
#include <stdio.h>

int testHeap()
{
    minheap *mh = createMinHeap(10);
    int ia = 73;
    heapdata *a = createHeapData(3, &ia);
    insert(mh, a);

    int ic = 42;
    heapdata *c = createHeapData(1, &ic);
    insert(mh, c);

    int ib = 66;
    heapdata *b = createHeapData(6, &ib);
    insert(mh, b);

    printf("%i\t%i\n", getKey(mh, 0), *(int *)getData(mh, 0));
    printf("%i\t%i\n", getKey(mh, 1), *(int *)getData(mh, 1));
    printf("%i\t%i\n", getKey(mh, 2), *(int *)getData(mh, 2));
    printf("%i\n", extractMin(mh)->key);
    printf("%i\n", extractMin(mh)->key);
}