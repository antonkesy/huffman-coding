#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint32_t key;
    void *data;
} heapdata_t;

typedef struct
{
    heapdata_t **elements;
    uint32_t size;
    uint32_t capacity;
} minheap_t;

minheap_t *create_min_heap_minheap(uint32_t maxcap);
heapdata_t *create_heap_data_minheap(uint32_t key, void *data);
uint32_t get_key_minheap(minheap_t *minheap, uint32_t  index);
void *get_data_minheap(minheap_t *minheap, uint32_t index);
uint32_t index_parent_minheap(uint32_t index);
uint32_t index_left_minheap(uint32_t index);
uint32_t index_right_minheap(uint32_t index);
uint32_t insert_minheap(minheap_t *minheap, heapdata_t *data);
void extract_min_data(minheap_t *minheap, void** out_data);
void min_heapify(minheap_t *minheap, uint32_t index);

void swap_heapdata(heapdata_t **i1, heapdata_t **i2);
void delete_minheap(minheap_t *minheap);