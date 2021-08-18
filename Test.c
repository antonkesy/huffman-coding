#include <stdio.h>
#include <string.h>
#include "huffman.h"

#define DEBUG

int main(void)
{
    //TODO add cmake test
    //should be 100 0 11 11 101 101 101 0 0 11 0 11 0 11 0
    //          1000 1111 1011 0110 1001 1011 0110
    char *testString = "BCAADDDCCACACAC";
    HuffmanData *hd = GetHuffmanData(testString, strlen(testString));
    printCodedString(hd);

#ifndef DEBUG
    getchar();
#endif
    return 0;
}
