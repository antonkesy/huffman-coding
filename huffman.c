#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue/priorityqueue.h"

//TODO free memory

int SortItemComparator(const void *first, const void *second)
{
    return (*(size_t *)first) - (*(size_t *)second);
}

SortedItems *SortItemsByFrequency(char *items, size_t size)
{
    SortedItems *sortedItems = malloc(sizeof(SortedItems));
    size_t *freqOfPosition = calloc(0xFF, sizeof(size_t));
    register size_t uniqueCharsCount = 0U;

    if (freqOfPosition != NULL)
    {
        for (register size_t i = 0U; i < size; ++i)
        {
            if (freqOfPosition[items[i]]++ == 0)
            {
                ++uniqueCharsCount;
            }
        }

        SortItem *sortItemsArray = malloc(sizeof(SortItem) * uniqueCharsCount);
        if (sortItemsArray != NULL)
        {
            register size_t i = 0U;
            for (register size_t j = 0U; j < 0xFF; ++j)
            {
                if (freqOfPosition[j] != 0)
                {
                    sortItemsArray[i].value = j;
                    sortItemsArray[i].freq = freqOfPosition[j];
                    ++i;
                }
            }
        }
        else
        {
            printf("malloc error");
        }

        qsort(sortItemsArray, uniqueCharsCount, sizeof(SortItem), SortItemComparator);

        sortedItems->items = sortItemsArray;
        sortedItems->size = uniqueCharsCount;
    }
    else
    {
        //MALLOC ERROR
        printf("malloc error");
    }
    free(freqOfPosition);

    return sortedItems;
}

HuffmanData *GetHuffmanData(char *items, size_t size)
{
    //error check
    return CodeIntoHuffmanString(items, size, SortItemsByFrequency(items, size));
}

HuffmanTree *BuildHuffmanTree(SortedItems *sortedItems)
{
    HuffmanNode *root = NULL;
    priorityque *prioQ = createPQ(NodeComparator);
    HuffmanNode *nodes = (HuffmanNode *)calloc(sizeof(HuffmanNode), sortedItems->size);

    for (register size_t i = 0U; i < sortedItems->size; ++i)
    {
        nodes[i].freq = sortedItems->items[sortedItems->size - i - 1].freq;
        nodes[i].value = sortedItems->items[sortedItems->size - i - 1].value;
        push(prioQ, &nodes[i]);
    }

    while (prioQ->size > 1)
    {
        HuffmanNode *left = pop(prioQ);
        HuffmanNode *right = pop(prioQ);
        HuffmanNode *parent = createParentHuffmanNode(left, right);
        push(prioQ, parent);
    }
    HuffmanTree *heap = malloc(sizeof(HuffmanTree));
    heap->root = pop(prioQ);
    heap->size = sortedItems->size;

    //free(prioQ);
    return heap;
}

void printHuffmanTree(HuffmanTree *heap)
{
    printf("Print heap:\n");
    if (heap->root == NULL)
    {
        printf("Heap empty!\n");
    }
    else
    {
        printHuffmanNodes(heap->root);
    }
}

void printHuffmanNodes(HuffmanNode *node)
{
    if (node != NULL)
    {
        printf("node -> ");
        if (node->left != NULL && node->right != NULL)
        {
            printf("parent node sum = %u\n", node->freq);
            //parent node (should always have 2 children)
            printf("parent node %u left = ", node->freq);
            printHuffmanNodes(node->left);
            printf("parent node %u right = ", node->freq);
            printHuffmanNodes(node->right);
        }
        else
        {
            //value node
            printf("value node %c %u\n", node->value, node->freq);
        }
    }
}

HuffmanNode *createValueHuffmanNode(SortItem *sortItem)
{
    //TODO check malloc error!
    HuffmanNode *newNode = calloc(sizeof(HuffmanNode), 1);
    newNode->value = sortItem->value;
    newNode->freq = sortItem->freq;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

HuffmanNode *createParentHuffmanNode(HuffmanNode *leftChild, HuffmanNode *rightChild)
{
    //TODO check malloc error!
    HuffmanNode *parentNode = calloc(sizeof(HuffmanNode), 1);
    parentNode->left = leftChild;
    parentNode->right = rightChild;
    parentNode->freq = leftChild->freq + rightChild->freq;

    return parentNode;
}

void delteHuffmanNodes(HuffmanNode *node)
{
    if (node != NULL)
    {
        if (node->left != NULL)
        {
            delteHuffmanNodes(node->left);
        }
        if (node->right != NULL)
        {
            delteHuffmanNodes(node->right);
        }
        free(node);
    }
}

HuffmanData *CodeIntoHuffmanString(char input[], size_t size, SortedItems *sortedItems)
{
    HuffmanTree *tree = BuildHuffmanTree(sortedItems);
    HuffmanCode *codes = malloc(sizeof(HuffmanCode) * 0xFF);
    HuffmanData *data = malloc(sizeof(HuffmanData));

    if (codes != NULL && data != NULL)
    {
        FillCodesForChar(codes, tree->root, 0, 0);

        data->bits = getCountOfBitsOutput(sortedItems, codes);
        //+1 for reminder
        data->codeStringSize = data->bits / 8U + 1;
        data->codedString = calloc(1, data->codeStringSize);
        data->items = sortedItems;
        convertInputIntoCodedString(input, size, data->codedString, codes);
    }
    else
    {
        printf("malloc error");
    }

    return data;
}

void FillCodesForChar(HuffmanCode *codes, HuffmanNode *node, char codeValue, size_t step)
{
    //only need to check one side because parent has always two
    if (node->left == NULL)
    {
        codes[node->value].code = codeValue;
        codes[node->value].size = step;
    }
    else
    {
        FillCodesForChar(codes, node->left, codeValue << 1, step + 1);
        FillCodesForChar(codes, node->right, (codeValue << 1) + 1, step + 1);
    }
}

void convertInputIntoCodedString(char src[], size_t srcSize, char dest[], HuffmanCode *codes)
{
    size_t nextWriteBit = 0U;
    char overflow = 0;
    char overflowSize = 0;

    for (register size_t i = 0U; i < srcSize; ++i)
    {
        //get rid of overflow before loading new code
        writeOverflow(dest, &overflow, &overflowSize, &nextWriteBit);

        int shifts = 8 - nextWriteBit % 8 - codes[src[i]].size;
        char writeByte = codes[src[i]].code;
        //negative shift if there is not enough space in current byte
        if (shifts < 0)
        {
            writeByte >>= (-1 * shifts);
            overflowSize = 8 + shifts;
            overflow = codes[src[i]].code << overflowSize;
        }
        else
        {
            writeByte <<= shifts;
        }

        dest[nextWriteBit / 8] += writeByte;

        nextWriteBit += codes[src[i]].size;
    }
    //write last overflow
    writeOverflow(dest, &overflow, &overflowSize, &nextWriteBit);
}

void writeOverflow(char *dest, char *overflow, char *overflowSize, size_t *nextWriteBit)
{
    if (*overflowSize != 0)
    {
        dest[*nextWriteBit / 8] += *overflow;
        *overflowSize = 0;
    }
}

size_t getCountOfBitsOutput(SortedItems *sortedItems, HuffmanCode *codes)
{
    size_t size = 0U;

    for (register size_t i = 0U; i < sortedItems->size; ++i)
    {
        size += codes[sortedItems->items[i].value].size * sortedItems->items[i].freq;
    }
    return size;
}

size_t countBits(size_t n)
{
    //log2(n)+1 maybe too slow
    size_t count = 0;
    while (n)
    {
        ++count;
        n >>= 1;
    }
    return count;
}

void printCharAsBinary(char c)
{

    size_t flag = 0x80;
    for (register char i = 0; i < 8; ++i)
    {
        printf("%c", (flag & c) == flag ? '1' : '0');
        if (((i + 1) % 4) == 0 && i != 31)
        {
            printf("_");
        }
        flag >>= 1;
    }
}

void printCodedString(HuffmanData *hd)
{
    for (register size_t i = 0; i < hd->codeStringSize; ++i)
    {
        printCharAsBinary(hd->codedString[i]);
        printf(" ");
    }
}

int decodeHuffmanData(HuffmanData *hd, char *dest, size_t size)
{
    HuffmanTree *hh = BuildHuffmanTree(hd->items);

    register size_t bit = 0U;
    register size_t destPos = 0U;

    for (size_t i = 0; i < size; i++)
    {
        HuffmanNode *currentNode = hh->root;
        while (currentNode->left != NULL)
        {
            char read = hd->codedString[bit / 8];
            if (((read >> (7 - (bit % 8))) & 1) == 0)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode = currentNode->right;
            }
            ++bit;
        }
        dest[destPos++] = currentNode->value;
    }
}

void deleteHuffmanHeap(HuffmanTree *heap)
{
    delteHuffmanNodes(heap->root);
    free(heap);
}

size_t getItemsSum(SortedItems *items)
{
    size_t sum = 0U;
    for (register size_t i = 0; i < items->size; ++i)
    {
        sum += items->items[i].freq;
    }
    return sum;
}

void deleteHuffmanData(HuffmanData *data)
{

    free(data->codedString);
    deleteSortedItems(data->items);
    free(data);
}

void deleteSortedItems(SortedItems *items)
{
    for (register size_t i = 0; i < items->size; ++i)
    {
        //TODO crashes here
        //    free(&(items->items[i]));
    }
    free(items);
}

int NodeComparator(const void *first, const void *second)
{
    return (*(size_t *)first) - (*(size_t *)second);
}

void printHuffmanNode(void *node)
{
    HuffmanNode *hNode = (HuffmanNode *)node;
    if (hNode->left == NULL && hNode->right == NULL)
    {
        printf("Value Node = %i %c\n", hNode->freq, hNode->value);
    }
    else
    {
        printf("Parent node = %i\n", hNode->freq);
    }
}