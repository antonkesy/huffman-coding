#include <stddef.h>

typedef struct
{
    int key;
    void *data;
} heapdata;

typedef struct
{
    heapdata **elements;
    size_t size;
    size_t capacity;
} minheap;

minheap *create_min_heap(size_t maxcap);
heapdata *create_heap_data(int key, void *data);
int get_key(minheap *minheap, size_t index);
void *get_data(minheap *minheap, size_t index);
int _index_parent(size_t index);
int _index_left(size_t index);
int _index_right(size_t index);
int insert(minheap *minheap, heapdata *data);
heapdata *extract_min(minheap *minheap);
void minHeapify(minheap *minheap, size_t index);

void swap_heapdata(heapdata **i1, heapdata **i2);