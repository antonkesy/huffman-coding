#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>

#define MAX_TREE_HEIGHT 50

typedef struct
{
    unsigned char size;
    char code;
} HuffmanCode;

struct Node
{
    size_t freq;
    char value;
    struct Node *left, *right;
};

typedef struct Node HuffmanNode;

typedef struct
{
    size_t size;
    HuffmanNode *root;
} HuffmanTree;

typedef struct
{
    int freq;
    char value;
} SortItem;

typedef struct
{
    size_t size;
    SortItem *items;
} SortedItems;

typedef struct
{
    size_t lenght;
    char *string;
} HuffmanString;

typedef struct
{
    size_t bits;
    size_t codeStringSize; //calculate from sortedItems count?
    unsigned char *codedString;
    SortedItems *items;
} HuffmanData;

//TODO return value is int and output is parameter
HuffmanData *GetHuffmanData(char *items, size_t size);
int SortItemComparator(const void *first, const void *second);
int NodeComparator(const void *first, const void *second);
SortedItems *SortItemsByFrequency(char *items, size_t size);
HuffmanTree *BuildHuffmanTree(SortedItems *sortedItems);
void printHuffmanTree(HuffmanTree *heap);
void printHuffmanNodes(HuffmanNode *node);
void printHuffmanNode(void *node);
HuffmanNode *createValueHuffmanNode(SortItem *sortItem);
HuffmanNode *createParentHuffmanNode(HuffmanNode *leftChild, HuffmanNode *rightChild);
void delteHuffmanNodes(HuffmanNode *root);
void deleteHuffmanHeap(HuffmanTree *heap);
void deleteHuffmanData(HuffmanData *data);
void deleteSortedItems(SortedItems *items);
HuffmanData *CodeIntoHuffmanString(char input[], size_t size, SortedItems *sortedItems);
void FillCodesForChar(HuffmanCode *codes, HuffmanNode *node, char codeValue, size_t step);
void convertInputIntoCodedString(char src[], size_t srcSize, char dest[], HuffmanCode *codes);
size_t getCountOfBitsOutput(SortedItems *sortedItems, HuffmanCode *codes);
size_t countBits(size_t n);
void printCharAsBinary(char c);
void printCodedString(HuffmanData *hd);
int decodeHuffmanData(HuffmanData *hd, char *dest, size_t size);
size_t getItemsSum(SortedItems *items);
void writeOverflow(char *dest, char *overflow, char *overflowSize, size_t *nextWriteBit);
#endif