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

minheap *createMinHeap(size_t maxcap);
heapdata *createHeapData(int key, void *data);
int isElementEmpty(minheap *minheap, size_t index);
int getKey(minheap *minheap, size_t index);
void *getData(minheap *minheap, size_t index);
int indexParent(size_t index);
int indexLeft(size_t index);
int indexRight(size_t index);
int insert(minheap *minheap, heapdata *data);
heapdata *extractMin(minheap *minheap);
void minHeapify(minheap *minheap, size_t index);
void printMinHeap(minheap *minheap);
void printHeight(minheap *minheap, size_t height);

void swap(heapdata **i1, heapdata **i2);