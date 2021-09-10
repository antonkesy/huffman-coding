#include <stddef.h>

typedef struct
{
    unsigned long key;
    void *data;
} heapdata;

typedef struct
{
    heapdata **elements;
    size_t size;
    size_t capacity;
} minheap;

minheap *create_min_heap_minheap(size_t maxcap);
heapdata *create_heap_data_minheap(unsigned long key, void *data);
unsigned long get_key_minheap(minheap *minheap, size_t index);
void *get_data_minheap(minheap *minheap, size_t index);
size_t _index_parent_minheap(size_t index);
size_t _index_left_minheap(size_t index);
size_t _index_right_minheap(size_t index);
size_t insert_minheap(minheap *minheap, heapdata *data);
heapdata *extract_min(minheap *minheap);
void min_heapify(minheap *minheap, size_t index);

void swap_heapdata(heapdata **i1, heapdata **i2);
void print_min_heap(minheap *minheap);

void delete_minheap(minheap *minheap);