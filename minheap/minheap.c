#include "minheap.h"
#include <stdlib.h>

heapdata *createHeapData(int key, void *data)
{
    heapdata *hd = malloc(sizeof(heapdata));
    hd->data = data;
    hd->key = key;
    return hd;
}

minheap *createMinHeap(size_t maxcap)
{
    minheap *mh = malloc(sizeof(minheap));
    mh->capacity = maxcap;
    mh->size = 0;
    mh->elements = malloc(sizeof(heapdata *) * maxcap);
    return mh;
}

int indexParent(size_t index)
{
    return (index - 1) / 2;
}

int indexLeft(size_t index)
{
    return (2 * index + 1);
}

int indexRight(size_t index)
{
    return (2 * index + 2);
}

int getKey(minheap *minheap, size_t index)
{
    return (*(minheap->elements[index])).key;
}

void *getData(minheap *minheap, size_t index)
{
    return (*(minheap->elements[index])).data;
}

int isElementEmpty(minheap *minheap, size_t index)
{
    return minheap->elements != NULL && minheap->elements[index] == NULL;
}

heapdata *extractMin(minheap *minheap)
{
    if (minheap->size == 0)
    {
        return NULL;
    }
    --(minheap->size);

    heapdata *root = minheap->elements[0];
    minheap->elements[0] = minheap->elements[1];

    if (minheap->size != 1)
    {
        minHeapify(minheap, 0);
    }

    return root;
}
void minHeapify(minheap *minheap, size_t index)
{
    int l = indexLeft(index);
    int r = indexRight(index);
    int smallest = index;

    if (l < minheap->size && getKey(minheap, l) < getKey(minheap, index))
    {
        smallest = l;
    }
    if (r < minheap->size && getKey(minheap, r) < getKey(minheap, smallest))
    {
        smallest = r;
    }
    if (smallest != index)
    {
        swap(&minheap->elements[index], &minheap->elements[smallest]);
        minHeapify(minheap, smallest);
    }
}

void printHeight(minheap *minheap, size_t height)
{
}

void printMinHeap(minheap *minheap)
{
    //TODO
}

void swap(heapdata **i1, heapdata **i2)
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
    ++(minheap->size);
    int index = minheap->size - 1;
    minheap->elements[index] = data;

    while (index != 0 && getKey(minheap, indexParent(index)) > getKey(minheap, index))
    {
        swap(&minheap->elements[index], &minheap->elements[indexParent(index)]);
        index = indexParent(index);
    }
    return index;
}