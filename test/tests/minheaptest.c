#include <stdlib.h>
#include <assert.h>
#include "../../src/minheap/minheap.h"
#include "../../src/huffman.h"

#define RANGE 100

int test_min_heap() {
    minheap_t *mh = create_min_heap_minheap(10);
    int ia = 73;
    heapdata_t *a = create_heap_data_minheap(3, &ia);
    insert_minheap(mh, a);

    int ic = 42;
    heapdata_t *c = create_heap_data_minheap(1, &ic);
    insert_minheap(mh, c);

    int ib = 66;
    heapdata_t *b = create_heap_data_minheap(6, &ib);
    insert_minheap(mh, b);

    free(a);
    free(b);
    free(c);
    delete_minheap(mh);

    return 0;
}

int heap_test_range() {
    minheap_t *mh = create_min_heap_minheap(RANGE);
    assert(mh);
    int *numbers = malloc(sizeof(int) * RANGE);
    assert(numbers);
    heapdata_t **data = malloc(sizeof(heapdata_t *) * RANGE);
    assert(data);

    for (int i = 0; i < RANGE; ++i) {
        numbers[i] = RANGE - i;
        data[i] = create_heap_data_minheap(numbers[i], &numbers[i]);
        assert(data[i]);
        insert_minheap(mh, data[i]);
    }

    delete_minheap(mh);
    for (size_t i = 0U; i < RANGE; ++i)
        free(data[i]);
    free(data);
    free(numbers);

    return 0;
}

int heap_test_huffman_nodes() {
    minheap_t *mh = create_min_heap_minheap(10);
    assert(mh);

    HuffmanNode a;
    a.freq = 3;
    HuffmanNode b;
    b.freq = 1;

    heapdata_t *data[3];
    data[0] = create_heap_data_minheap(3, &a);
    assert(data[0]);
    data[1] = create_heap_data_minheap(1, &b);
    assert(data[1]);

    insert_minheap(mh, data[0]);
    insert_minheap(mh, data[1]);

    HuffmanNode *left;
    extract_min_data(mh, (void *) &left);
    HuffmanNode *right;
    extract_min_data(mh, (void *) &right);

    HuffmanNode *parent = create_parent_huffman_node(left, right);
    assert(parent);
    data[2] = create_heap_data_minheap(parent->freq, parent);
    assert(data[2]);
    insert_minheap(mh, data[2]);

    delete_minheap(mh);
    assert(mh!=NULL);
    free(parent);
    free(data[2]);

    return 0;
}

int main() {
    return heap_test_range() + test_min_heap() + heap_test_huffman_nodes();
}