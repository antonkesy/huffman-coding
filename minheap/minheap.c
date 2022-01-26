#include "minheap.h"
#include <stdlib.h>

heapdata_t *create_heap_data_minheap(uint32_t key, void *data)
{
    heapdata_t *hd = malloc(sizeof(heapdata_t));
    hd->data = data;
    hd->key = key;
    return hd;
}

minheap_t *create_min_heap_minheap(uint32_t maxcap)
{
    minheap_t *mh = malloc(sizeof(minheap_t));
    mh->capacity = maxcap;
    mh->size = 0;
    mh->elements = malloc(sizeof(heapdata_t *) * maxcap);
    return mh;
}

uint32_t index_parent_minheap(uint32_t index)
{
    return (index - 1) / 2;
}

uint32_t index_left_minheap(uint32_t index)
{
    return (2 * index + 1);
}

uint32_t index_right_minheap(uint32_t index)
{
    return (2 * index + 2);
}

uint32_t get_key_minheap(minheap_t *minheap, uint32_t index)
{
    return (*(minheap->elements[index])).key;
}

void *get_data_minheap(minheap_t *minheap, uint32_t index)
{
    return (*(minheap->elements[index])).data;
}

void extract_min_data(minheap_t *minheap, void **out_data)
{
    if (minheap->size == 0)
    {
        return;
    }
    --(minheap->size);

    heapdata_t *root = minheap->elements[0];
    minheap->elements[0] = minheap->elements[minheap->size];

    if (minheap->size > 1)
    {
        min_heapify(minheap, 0);
    }

    *out_data = root->data;
    free(root);
}

void min_heapify(minheap_t *minheap, uint32_t index)
{
    uint32_t l = index_left_minheap(index);
    uint32_t r = index_right_minheap(index);
    uint32_t smallest = index;

    if (l < minheap->size && get_key_minheap(minheap, l) < get_key_minheap(minheap, index))
    {
        smallest = l;
    }
    if (r < minheap->size && get_key_minheap(minheap, r) < get_key_minheap(minheap, smallest))
    {
        smallest = r;
    }
    if (smallest != index)
    {
        swap_heapdata(&minheap->elements[index], &minheap->elements[smallest]);
        min_heapify(minheap, smallest);
    }
}

void swap_heapdata(heapdata_t **i1, heapdata_t **i2)
{
    heapdata_t *tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

uint32_t insert_minheap(minheap_t *minheap, heapdata_t *data)
{
    if (minheap->size == minheap->capacity)
    {
        return -1;
    }
    size_t index = minheap->size;
    ++(minheap->size);
    minheap->elements[index] = data;

    while (index != 0 && get_key_minheap(minheap, index_parent_minheap(index)) > get_key_minheap(minheap, index))
    {
        swap_heapdata(&minheap->elements[index], &minheap->elements[index_parent_minheap(index)]);
        index = index_parent_minheap(index);
    }
    return index;
}

void delete_minheap(minheap_t *minheap)
{
    if (minheap != NULL)
    {
        free(minheap->elements);
        free(minheap);
    }
}