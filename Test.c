#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include <stddef.h>

#define DEBUG

int main(void)
{
    char *testString = "abcdef";
    HuffmanData *hd = GetHuffmanData(testString, strlen(testString));
    size_t destSize = getItemsSum(hd->items);
    char *dest = malloc(destSize + 1);
    decodeHuffmanData(hd, dest, destSize);
    dest[destSize] = '\0';
    printf("%s\n%s", testString, dest);
    printf("\n%u", strcmp(testString, dest));

#ifndef DEBUG
    getchar();
#endif
    return 0;
}
