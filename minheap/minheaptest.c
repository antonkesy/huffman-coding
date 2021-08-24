#include "minheaptest.h"
#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>
#include "../huffman.h"

int test_min_heap()
{
    minheap *mh = create_min_heap_minheap(10);
    int ia = 73;
    heapdata *a = create_heap_data_minheap(3, &ia);
    insert_minheap(mh, a);

    int ic = 42;
    heapdata *c = create_heap_data_minheap(1, &ic);
    insert_minheap(mh, c);

    int ib = 66;
    heapdata *b = create_heap_data_minheap(6, &ib);
    insert_minheap(mh, b);

    printf("%i\t%i\n", get_key_minheap(mh, 0), *(int *)get_data_minheap(mh, 0));
    printf("%i\t%i\n", get_key_minheap(mh, 1), *(int *)get_data_minheap(mh, 1));
    printf("%i\t%i\n", get_key_minheap(mh, 2), *(int *)get_data_minheap(mh, 2));
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

    minheap *mh = create_min_heap_minheap(100);
    int *numbers = malloc(sizeof(int) * 100);

    for (int i = 0; i < 100; ++i)
    {
        numbers[i] = 100 - i;
        insert_minheap(mh, create_heap_data_minheap(numbers[i], &numbers[i]));
    }
    //print_min_heap(mh);

    for (int i = 0; i < 100; ++i)
    {
        printf("%i\t", extract_min(mh)->key);
    }

    free(mh);

    return 0;
}

int heap_test_huffman_nodes()
{
    minheap *mh = create_min_heap_minheap(10);
    HuffmanNode a;
    a.freq = 3;
    HuffmanNode b;
    b.freq = 1;
    insert_minheap(mh, create_heap_data_minheap(3, &a));
    insert_minheap(mh, create_heap_data_minheap(1, &b));
    printf("\n");
    print_min_heap(mh);

    HuffmanNode *left = extract_min(mh)->data;
    HuffmanNode *right = extract_min(mh)->data;
    printf("\n");
    print_min_heap(mh);

    HuffmanNode *parent = _create_parent_huffman_node(left, right);
    insert_minheap(mh, create_heap_data_minheap(parent->freq, parent));

    printf("\n");
    print_min_heap(mh);

    return 0;
}