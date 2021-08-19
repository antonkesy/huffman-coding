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
    char value;
    unsigned int freq;
    struct Node *left, *right;
};

typedef struct Node HuffmanNode;

typedef struct
{
    unsigned int size;
    HuffmanNode *root;
} HuffmanHeap;

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

typedef struct
{
    unsigned int lenght;
    char *string;
} HuffmanString;

typedef struct
{
    unsigned int bits;
    unsigned int codeStringSize; //calculate from sortedItems count?
    unsigned char *codedString;
    SortedItems *items;
} HuffmanData;

//TODO return value is int and output is parameter
HuffmanData *GetHuffmanData(char *items, unsigned int size);
int SortItemComparator(const void *first, const void *second);
SortedItems *SortItemsByFrequency(char *items, unsigned int size);
HuffmanHeap *BuildHuffmanHeap(SortedItems *sortedItems);
void printHuffmanHeap(HuffmanHeap *heap);
void printHuffmanNodes(HuffmanNode *node);
HuffmanNode *createValueHuffmanNode(SortItem *sortItem);
HuffmanNode *createParentHuffmanNode(HuffmanNode *leftChild, HuffmanNode *rightChild);
void delteHuffmanNodes(HuffmanNode *root);
void deleteHuffmanHeap(HuffmanHeap *heap);
void deleteHuffmanData(HuffmanData *data);
void deleteSortedItems(SortedItems *items);
HuffmanData *CodeIntoHuffmanString(char input[], unsigned int size, SortedItems *sortedItems);
void FillCodesForChar(HuffmanCode *codes, HuffmanNode *node, char codeValue, unsigned int step);
void convertInputIntoCodedString(char src[], unsigned int srcSize, char dest[], HuffmanCode *codes);
unsigned int getCountOfBitsOutput(SortedItems *sortedItems, HuffmanCode *codes);
unsigned int countBits(unsigned int n);
void printLongAsBinary(char c);
void printCodedString(HuffmanData *hd);
int decodeHuffmanData(HuffmanData *hd, char *dest, size_t size);
unsigned int getItemsSum(SortedItems *items);
#endif