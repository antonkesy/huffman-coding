#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "huffman.h"
#include "priorityqueue/priorityqueue.h"
#include "priorityqueue/priorityqueuetest.h"
#define DEBUG

int testHuffman()
{
    char *testString = "Only need to fix the last byte to be written complete and cut. There are also many memory leaks :)";
    HuffmanData *hd = GetHuffmanData(testString, strlen(testString));
    size_t destSize = getItemsSum(hd->items);
    char *dest = malloc(destSize + 1);
    decodeHuffmanData(hd, dest, destSize);
    dest[destSize] = '\0';
    printf("%s\n%s\n", testString, dest);
    size_t compareValue = strcmp(testString, dest);
    printf("compare should be 0 = %u", compareValue);
    return compareValue;
}

int main(void)
{
    // printf("priority queue test failed ? %i", testPriorityQueue());
    printf("huffman test failed ? %i", testHuffman());

#ifndef DEBUG
    //getchar();
#endif
    return 0;
}
