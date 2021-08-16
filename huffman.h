#ifndef HUFFMAN_H
#define HUFFMAN_H

#define MAX_TREE_HEIGHT 50

struct Node
{
    char item;
    unsigned int freq;
    struct Node *left, *right;
};

typedef struct Node HuffmanNode;

typedef struct
{
    unsigned int size;
    unsigned int capacity;
    struct HuffmanNode **nodes;
} Heap;

typedef struct
{
    unsigned int size;
    unsigned int *items;
    Heap hoffmanHeap;
} HuffmanData;

typedef struct
{
    int freq;
    char value;
} SortItem;

typedef struct
{
    unsigned int size;
    SortItem *items;
} SortedItems;

HuffmanData GetHuffmanData(char *items, unsigned int size);
int SortItemComparator(const void *first, const void *second);
SortedItems SortItemsByFrequency(char *items, unsigned int size);
Heap GetHuffmanHeap(char *items, unsigned int *freq, unsigned int size);

#endif