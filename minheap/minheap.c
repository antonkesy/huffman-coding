#include "minheap.h"
#include <stdlib.h>
#include <stdio.h>

heapdata *create_heap_data(int key, void *data)
{
    heapdata *hd = malloc(sizeof(heapdata));
    hd->data = data;
    hd->key = key;
    return hd;
}

minheap *create_min_heap(size_t maxcap)
{
    minheap *mh = malloc(sizeof(minheap));
    mh->capacity = maxcap;
    mh->size = 0;
    mh->elements = malloc(sizeof(heapdata *) * maxcap);
    return mh;
}

int _index_parent(size_t index)
{
    return (index - 1) / 2;
}

int _index_left(size_t index)
{
    return (2 * index + 1);
}

int _index_right(size_t index)
{
    return (2 * index + 2);
}

int get_key(minheap *minheap, size_t index)
{
    return (*(minheap->elements[index])).key;
}

void *get_data(minheap *minheap, size_t index)
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
void min_heapify(minheap *minheap, size_t index)
{
    int l = _index_left(index);
    int r = _index_right(index);
    int smallest = index;

    if (l < minheap->size && get_key(minheap, l) < get_key(minheap, index))
    {
        smallest = l;
    }
    if (r < minheap->size && get_key(minheap, r) < get_key(minheap, smallest))
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

int insert(minheap *minheap, heapdata *data)
{
    if (minheap->size == minheap->capacity)
    {
        return -1;
    }
    int index = minheap->size;
    ++(minheap->size);
    minheap->elements[index] = data;

    while (index != 0 && get_key(minheap, _index_parent(index)) > get_key(minheap, index))
    {
        swap_heapdata(&minheap->elements[index], &minheap->elements[_index_parent(index)]);
        index = _index_parent(index);
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
