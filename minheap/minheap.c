#include "minheap.h"
#include <stdlib.h>
#include <stdio.h>

heapdata *create_heap_data_minheap(uint32_t key, void *data)
{
    heapdata *hd = malloc(sizeof(heapdata));
    hd->data = data;
    hd->key = key;
    return hd;
}

minheap *create_min_heap_minheap(uint32_t maxcap)
{
    minheap *mh = malloc(sizeof(minheap));
    mh->capacity = maxcap;
    mh->size = 0;
    mh->elements = malloc(sizeof(heapdata *) * maxcap);
    return mh;
}

uint32_t _index_parent_minheap(uint32_t index)
{
    return (index - 1) / 2;
}

uint32_t _index_left_minheap(uint32_t index)
{
    return (2 * index + 1);
}

uint32_t _index_right_minheap(uint32_t index)
{
    return (2 * index + 2);
}

uint32_t get_key_minheap(minheap *minheap, uint32_t index)
{
    return (*(minheap->elements[index])).key;
}

void *get_data_minheap(minheap *minheap, uint32_t index)
{
    return (*(minheap->elements[index])).data;
}

heapdata *extract_min(minheap *minheap)
{
    if (minheap->size == 0)
    {
        return NULL;
    }
    --(minheap->size);

    heapdata *root = minheap->elements[0];
    minheap->elements[0] = minheap->elements[minheap->size];

    if (minheap->size > 1)
    {
        min_heapify(minheap, 0);
    }

    return root;
}
void min_heapify(minheap *minheap, uint32_t index)
{
    uint32_t l = _index_left_minheap(index);
    uint32_t r = _index_right_minheap(index);
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

void swap_heapdata(heapdata **i1, heapdata **i2)
{
    heapdata *tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

uint32_t insert_minheap(minheap *minheap, heapdata *data)
{
    if (minheap->size == minheap->capacity)
    {
        return -1;
    }
    size_t index = minheap->size;
    ++(minheap->size);
    minheap->elements[index] = data;

    while (index != 0 && get_key_minheap(minheap, _index_parent_minheap(index)) > get_key_minheap(minheap, index))
    {
        swap_heapdata(&minheap->elements[index], &minheap->elements[_index_parent_minheap(index)]);
        index = _index_parent_minheap(index);
    }
    return index;
}

void print_min_heap(minheap *minheap)
{
    for (int i = 0; i < minheap->size; ++i)
    {
        printf("%i\t", minheap->elements[i]->key);
    }
}

void delete_minheap(minheap* minheap){
    free(minheap->elements);
    free(minheap);
}