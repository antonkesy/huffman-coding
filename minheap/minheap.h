#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint32_t key;
    void *data;
} heapdata;

typedef struct
{
    heapdata **elements;
    uint32_t size;
    uint32_t capacity;
} minheap;

minheap *create_min_heap_minheap(uint32_t maxcap);
heapdata *create_heap_data_minheap(uint32_t key, void *data);
uint32_t get_key_minheap(minheap *minheap, uint32_t  index);
void *get_data_minheap(minheap *minheap, uint32_t index);
uint32_t _index_parent_minheap(uint32_t index);
uint32_t _index_left_minheap(uint32_t index);
uint32_t _index_right_minheap(uint32_t index);
uint32_t insert_minheap(minheap *minheap, heapdata *data);
void extract_min_data(minheap *minheap, void** out_data);
void min_heapify(minheap *minheap, uint32_t index);

void swap_heapdata(heapdata **i1, heapdata **i2);
void print_min_heap(minheap *minheap);

void delete_minheap(minheap *minheap);