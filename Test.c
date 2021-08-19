#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "huffman.h"
#include "priorityqueue/priorityqueue.h"
#define DEBUG

int testHuffman()
{
    char *testString = "abcdef";
    HuffmanData *hd = GetHuffmanData(testString, strlen(testString));
    size_t destSize = getItemsSum(hd->items);
    char *dest = malloc(destSize + 1);
    decodeHuffmanData(hd, dest, destSize);
    dest[destSize] = '\0';
    printf("%s\n%s", testString, dest);
    printf("\n%u", strcmp(testString, dest));
    return 1;
}

int main(void)
{
    if (testPriorityQueue() != 0)
    {
        printf("priority queue test failed");
    }
    if (testHuffman() != 0)
    {
        printf("huffman test failed");
    }

#ifndef DEBUG
    getchar();
#endif
    return 0;
}
